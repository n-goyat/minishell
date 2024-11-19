/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_pipeline.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maba <maba@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 14:57:02 by maba              #+#    #+#             */
/*   Updated: 2024/11/12 23:19:54 by maba             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pa_header.h"


static void handle_signal(int sig)
{
    // Envoyer le signal à tous les processus du groupe
    kill(0, sig);
}


void execute_pipeline(t_commands_list *cmd_list, t_env_list *env_list) 
{
    t_cmd_node *current = cmd_list->head;
    int pipefd[2];
    int in_fd = STDIN_FILENO;
    int is_last_cmd;
    pid_t pids[1024]; // Tableau pour stocker les PID des processus enfants
    int i = 0;

    // Configurer le gestionnaire de signal
    signal(SIGINT, handle_signal);

    while (current != NULL) 
    {
        is_last_cmd = (current->next == NULL);

        if (!is_last_cmd && pipe(pipefd) == -1) 
        {
            perror("pipe");
            exit(EXIT_FAILURE);
        }

        // Définir les sorties
        int out_fd = is_last_cmd ? STDOUT_FILENO : pipefd[1];
        // Créer un processus pour la commande actuelle
        pid_t pid = fork();
        if (pid == -1) 
        {
            perror("fork");
            exit(EXIT_FAILURE);
        }

        if (pid == 0) 
        {
            // Enfant : Configurer les redirections
            if (in_fd != STDIN_FILENO) 
            {
                dup2(in_fd, STDIN_FILENO);
                close(in_fd);
            }

            if (!is_last_cmd) 
            {
                dup2(out_fd, STDOUT_FILENO);
            }

            // Fermer les descripteurs inutiles
            close(pipefd[0]);
            close(pipefd[1]);

            execute_single_command(current, env_list);
            exit(0);
        } 
        else 
        {
            // Parent : Stocker le PID et gérer les descripteurs
            pids[i++] = pid;

            if (in_fd != STDIN_FILENO) 
                close(in_fd);

            if (!is_last_cmd) 
                close(pipefd[1]);

            in_fd = pipefd[0];
        }

        current = current->next;
    }
    int j = 0;
    // Attendre tous les processus enfants
    while (j < i) 
    {
        waitpid(pids[j], NULL, 0);
        j++;
    }
    // Restaurer le gestionnaire de signal par défaut
    signal(SIGINT, SIG_DFL);
}

static void execute_individual_command(t_cmd_node *current, t_env_list *env_list) 
{
    pid_t pid = fork();

    if (pid == -1) 
    {
        perror("fork");
        return;
    }
    if (pid == 0) 
    {
        execute_single_command(current, env_list);
        exit(0);
    } 
    else 
        ft_wait_for_processes(pid);
}


void handle_commands(t_commands_list *cmd_list, t_env_list *env_list) 
{
    t_cmd_node *current = cmd_list->head;

    if (current == NULL)
        return;

    if (cmd_list->size > 1)
        execute_pipeline(cmd_list, env_list);
    else 
    {
        while (current != NULL) 
        {
            if (is_builtin(current->cmd))
                ft_execute_builtin(current, env_list);
            else
                execute_individual_command(current, env_list);
            current = current->next;
        }
    }
}
