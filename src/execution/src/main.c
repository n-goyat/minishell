/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maba <maba@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 11:38:33 by maba              #+#    #+#             */
/*   Updated: 2024/10/21 21:38:06 by maba             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pa_header.h"
#include "pa_header.h"

int	main(int argc, char **argv, char **envp)
{
	t_env			*env_list;
	char			*input;
	t_commands_list	*cmd_list;
	t_token_list	*token_list;
	t_cmd_node		*current;

	(void)argc; // Marquer comme non utilisé
	(void)argv; // Marquer comme non utilisé
	env_list = init_env_list(envp);
	ft_handle_signals(); // Gérer les signaux
	while (1)
	{
		input = readline("minishell> ");
		env_list = init_env_list(envp);
		if (!input)
			break ;
		// Tokeniser l'entrée
		token_list = tokenize_input(input);
		// Parser l'entrée (utiliser le parsing de ton binôme)
		parse_and_group_commands(&cmd_list, &token_list, env_list);
		current = cmd_list->head;
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
		// Libérer les tokens et les commandes après l'exécution
		free(input);
		free_env_list(env_list);
	}
	free_env_list(env_list); // Libérer la mémoire des variables d'environnement
	return (0);
}
