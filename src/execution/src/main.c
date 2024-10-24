

#include "../includes/pa_header.h"
#include "pa_header.h"

int	check_syntax_errors(t_token_list *token_list)
{
	t_token	*current;
	int		expect_command;

	current = token_list->head;
	expect_command = 1;
	while (current)
	{
		if (current->type == TOKEN_PIPE)
		{
			if (expect_command || !current->next)
			{
				fprintf(stderr, "Syntax error: unexpected token `|'\n");
				return (1);
			}
			expect_command = 1;
		}
		else if (current->type == TOKEN_REDIRECT_IN
			|| current->type == TOKEN_REDIRECT_OUT)
		{
			if (!current->next || current->next->type != TOKEN_WORD)
			{
				fprintf(stderr, "Syntax error: unexpected token `%s'\n",
					current->value);
				return (1);
			}
			expect_command = 0;
		}
		else if (current->type == TOKEN_WORD)
		{
			expect_command = 0;
		}
		current = current->next;
	}
	return (0);
}

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
	//ft_handle_signals(); // Gérer les signaux
	while (1)
	{
		input = readline("minishell> ");
		env_list = init_env_list(envp);
		add_history(input);
		if (!input)
			break ;
		// Tokeniser l'entrée
		token_list = tokenize_input(input);
		if (check_syntax_errors(token_list) != 0)
		{
			// If there's a syntax error, free memory and continue
			//free_token_list(token_list);
			free(input);
			continue ;
		}
		// append tokens
		/*
			*
			*
			*/
		// Parser l'entrée (utiliser le parsing de ton binôme)
		parse_and_group_commands(&cmd_list, &token_list, env_list);
		current = cmd_list->head;
		while (current)
		{
			if (is_builtin(current->cmd))
				ft_execute_builtin(current, env_list);
			// else if (current->type == CMD_PIPE)
			// 	ft_execute_pipeline(current, env_list);
			else
				ft_execute_command(current, env_list);
			current = current->next;
		}
		// Libérer les tokens et les commandes après l'exécution
		free(input);
		free_env_list(env_list);
	}
	rl_clear_history();
	free_env_list(env_list); // Libérer la mémoire des variables d'environnement
	return (0);
}
