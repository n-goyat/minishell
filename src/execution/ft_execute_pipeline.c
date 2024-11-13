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

/**
 * ft_execute_pipeline() : Gère l'exécution des commandes connectées par des pipes (|), 
 * en redirigeant la sortie de la première commande vers l'entrée de la suivante, et ainsi de suite.
 * Entrée : Liste de commandes séparées par des pipes.
 * Utilise : pipe(), dup2(), fork(), execve().
*/

void execute_pipeline(t_commands_list *cmd_list, t_env_list *env_list) 
{
    t_cmd_node *current = cmd_list->head;
    int pipefd[2];
    int in_fd = 0;
    while (current != NULL) 
    {
        if (!ex_infile_check(current) || (needs_input(current) && in_fd == 0)) 
        {
            current = current->next;
            continue;
        }
        if (current->next != NULL && pipe(pipefd) == -1) 
        {
            perror("pipe");
            exit(EXIT_FAILURE);
        }
        if (current->next != NULL) 
            fork_and_execute(current, env_list, in_fd, pipefd[1]);
        else 
            fork_and_execute(current, env_list, in_fd, 1);
        if (in_fd != 0) 
            close(in_fd);
        if (current->next != NULL) 
        {
            close(pipefd[1]);
            in_fd = pipefd[0];
        }
        current = current->next;
    }
}

void handle_commands(t_commands_list *cmd_list, t_env_list *env_list) 
{
    t_cmd_node *current = cmd_list->head;
    if (cmd_list->size > 1)
        execute_pipeline(cmd_list, env_list);
    else
    {
        if (is_builtin(current->cmd))
            ft_execute_builtin(current, env_list);
        else
            ft_execute_command(current, env_list);
    }
}
