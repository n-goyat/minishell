/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_pipeline.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maba <maba@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 14:57:02 by maba              #+#    #+#             */
/*   Updated: 2024/10/21 11:12:48 by maba             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pa_header.h"

/**
 * ft_execute_pipeline() : Gère l'exécution des commandes connectées par des pipes (|), 
 * en redirigeant la sortie de la première commande vers l'entrée de la suivante, et ainsi de suite.
 * Entrée : Liste de commandes séparées par des pipes.
 * Utilise : pipe(), dup2(), fork(), execve().
*/

void ft_execute_pipeline(t_cmd_node *cmd, t_env *env_list)
{
    int pipefd[2];
    pid_t pid1, pid2;

    if (pipe(pipefd) == -1)  // Créer le pipe
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid1 = fork();
    if (pid1 == 0)  // Processus pour la première commande
    {
        dup2(pipefd[1], STDOUT_FILENO);  // Redirige la sortie vers le pipe
        close(pipefd[0]);
        close(pipefd[1]);

        if (cmd->files)
            ft_handle_redirection(cmd->files);  // Gérer les redirections

        char **envp = ft_copy_env(env_list);
        execve(cmd->cmd[0], cmd->cmd, envp);  // Exécuter la première commande
        perror("execve");
        exit(EXIT_FAILURE);
    }

    pid2 = fork();
    if (pid2 == 0)  // Processus pour la deuxième commande
    {
        dup2(pipefd[0], STDIN_FILENO);  // Redirige l'entrée vers le pipe
        close(pipefd[0]);
        close(pipefd[1]);

        char **envp = ft_copy_env(env_list);
        execve(cmd->next->cmd[0], cmd->next->cmd, envp);  // Exécuter la deuxième commande
        perror("execve");
        exit(EXIT_FAILURE);
    }

    close(pipefd[0]);
    close(pipefd[1]);

    ft_wait_for_processes(pid1);  // Attendre les deux processus
    ft_wait_for_processes(pid2);
}
