/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maba <maba@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 11:38:33 by maba              #+#    #+#             */
/*   Updated: 2024/11/19 17:57:14 by maba             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pa_header.h"

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
				perror("Syntax error: unexpected token `|");
				exit(EXIT_FAILURE);
			}
			expect_command = 1;
		}
		else if (current->type == TOKEN_REDIRECT_IN
			|| current->type == TOKEN_REDIRECT_OUT)
		{
			if (!current->next || current->next->type != TOKEN_WORD)
			{
				perror("Syntax error: unexpected token `");
					// ajouter token value
				exit(EXIT_FAILURE);
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

// Function to check for unmatched quotes in the input
int	quote_syntax(const char *input, int i)
{
	int	single_quotes;
	int	double_quotes;

	single_quotes = 0;
	double_quotes = 0;
	while (input[i] != '\0')
	{
		if (input[i] == '\'') // Single quote
			single_quotes++;
		else if (input[i] == '\"') // Double quote
			double_quotes++;
		i++;
	}
	if (single_quotes % 2 != 0)
	{
		perror("Syntax error: unmatched single quotes");
		return (0);
	}
	if (double_quotes % 2 != 0)
	{
		perror("Syntax error: unmatched double quotes");
		return (0);
	}
	return (1);
}

// dorker valgrind --leak-check=full  --suppressions=readline.supp --show-leak-kinds=all --track-origins=yes --verbose ./shell
// ==1194== 1,182 bytes in 39 blocks are definitely lost in loss record 81 of 117
// ==1194==    at 0x48407B4: malloc (vg_replace_malloc.c:381)
// ==1194==    by 0x10D0E5: ft_strjoin (in /dorker_workspace/4. Fourth Circle/minishell/src/shell)
// ==1194==    by 0x10A990: ft_copy_env (in /dorker_workspace/4. Fourth Circle/minishell/src/shell)
// ==1194==    by 0x109F5D: execute_single_command (in /dorker_workspace/4. Fourth Circle/minishell/src/shell)
// ==1194==    by 0x10A062: fork_and_execute (in /dorker_workspace/4. Fourth Circle/minishell/src/shell)
// ==1194==    by 0x10A0D5: ft_execute_command (in /dorker_workspace/4. Fourth Circle/minishell/src/shell)
// ==1194==    by 0x10A25E: handle_commands (in /dorker_workspace/4. Fourth Circle/minishell/src/shell)
// ==1194==    by 0x109598: main (in /dorker_workspace/4. Fourth Circle/
int	main(int argc, char **argv, char **envp)
{
	char			*input;
	t_env_list		*env_list;
	t_commands_list	*cmd_list;
	t_token_list	*token_list;
	t_cmd_node		*current;
	static int	counter;

	counter = 0;
	(void)current;
	(void)argc; // Marquer comme non utilisé
	(void)argv; // Marquer comme non utilisé
	setup_signal_handlers();
	disable_readline_signals();
	env_list = init_env_list(envp);
	if (!env_list)
	{
		perror("Failed to initialize environment list.\n");
		return (1);
	}
	while (1)
	{
		input = readline("minishell> ");
		if (!input)
		{
			printf("exit\n"); 
			if (input)
				free(input);
			break ;
		}
		if (!quote_syntax(input, 0))
			input = readline("minishell> ");
		add_history(input);
		token_list = tokenize_input(input, env_list);
		print_tokens(token_list);
		if (!token_list || check_syntax_errors(token_list) != 0)
		{
			free_token_list(token_list);
			free(input);
			continue ;
		}
		parse_and_group_commands(&cmd_list, &token_list, &env_list);
		current = cmd_list->head;
		print_cmd_list(cmd_list);
		handle_commands(cmd_list, env_list);
		free_token_list(token_list);
		free(input);
		counter++;
	}
	if (counter > 0)
	{
		rl_clear_history();
		if (env_list)
			free_env_list(env_list);
		if (cmd_list)
			free_cmd_list(cmd_list);
	}
	return (0);
}
