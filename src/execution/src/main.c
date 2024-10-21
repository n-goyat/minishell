/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maba <maba@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 11:38:33 by maba              #+#    #+#             */
/*   Updated: 2024/10/21 12:03:11 by maba             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pa_header.h"

int main(int argc, char **argv, char **envp)
{
    (void)argc;  // Marquer comme non utilisé
    (void)argv;  // Marquer comme non utilisé
    t_env *env_list = init_env_list(envp);
    char *input;
    t_commands_list *cmd_list;

    ft_handle_signals();  // Gérer les signaux

    while (1)
    {
        input = readline("minishell> ");
        if (!input)
            break;

        cmd_list = parse_input(input, env_list);  // Parser l'entrée

        t_cmd_node *current = cmd_list->head;
        while (current)
        {
            if (is_builtin(current->cmd))
                ft_execute_builtin(current, env_list);
            else if (current->type == CMD_PIPE)
                ft_execute_pipeline(current, env_list);
            else
                ft_execute_command(current, env_list);

            current = current->next;
        }

        free(input);  // Libérer la mémoire
    }

    free_env_list(env_list);  // Libérer la mémoire des variables d'environnement
    return 0;
}
