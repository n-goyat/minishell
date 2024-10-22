/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_pipeline.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maba <maba@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 14:57:02 by maba              #+#    #+#             */
/*   Updated: 2024/10/22 17:09:11 by maba             ###   ########.fr       */
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
    pid_t pid;
    t_cmd_node *current_cmd = cmd;

    // Créer des pipes et exécuter chaque commande
    while (current_cmd)
    {
        if (current_cmd->next)  // Si ce n'est pas la dernière commande
        {
            if (pipe(pipefd) == -1)  // Créer le pipe
            {
                perror("pipe");
                exit(EXIT_FAILURE);
            }
        }

        pid = fork();
        if (pid < 0)  // Erreur de fork
        {
            perror("fork");
            exit(EXIT_FAILURE);
        }
        else if (pid == 0)  // Processus enfant
        {
            if (current_cmd->next)  // Rediriger la sortie si ce n'est pas la dernière commande
            {
                dup2(pipefd[1], STDOUT_FILENO);  // Redirige la sortie vers le pipe
            }
            if (current_cmd->files)
            {
                ft_handle_redirection(current_cmd->files);  // Gérer les redirections
            }
            char **envp = ft_copy_env(env_list);
            execve(current_cmd->cmd[0], current_cmd->cmd, envp);  // Exécuter la commande
            perror("execve");
            exit(EXIT_FAILURE);
        }
        
        if (current_cmd->next)
        {
            close(pipefd[1]);  // Ferme l'extrémité d'écriture du pipe
            dup2(pipefd[0], STDIN_FILENO);  // Redirige l'entrée vers le pipe
            close(pipefd[0]);  // Ferme l'extrémité de lecture
        }

        current_cmd = current_cmd->next;  // Passer à la commande suivante
    }

    // Attendre que tous les processus enfants se terminent
    while (wait(NULL) > 0);
}
