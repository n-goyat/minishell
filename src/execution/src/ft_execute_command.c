/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_command.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maba <maba@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 14:56:55 by maba              #+#    #+#             */
/*   Updated: 2024/10/21 12:40:59 by maba             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pa_header.h"

/*
* ft_execute_command() : Fonction centrale qui exécute les commandes externes en utilisant fork() et execve().
*
* Entrée : Un tableau de tokens correspondant à une commande.
* Sortie : Le résultat de l'exécution.
*
*/

void ft_execute_command(t_cmd_node *cmd, t_env *env_list)
{
    pid_t pid;
    // int status;
    char **envp = ft_copy_env(env_list);  // Copier les variables d’environnement

    pid = fork();
    if (pid == 0)  // Processus enfant
    {
        // Gérer les redirections s'il y en a
        if (cmd->files)
            ft_handle_redirection(cmd->files);

        // Exécuter la commande externe avec execve
        if (execve(cmd->cmd[0], cmd->cmd, envp) == -1)
        {
            perror("execve");
            exit(EXIT_FAILURE);
        }
    }
    else if (pid < 0)  // Si fork échoue
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    else  // Processus parent
    {
        // Attendre la fin du processus enfant
        ft_wait_for_processes(pid);
    }

    free(envp);  // Libérer la mémoire des variables d'environnement
}
