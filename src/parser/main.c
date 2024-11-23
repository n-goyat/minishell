/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoyat <ngoyat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 11:38:33 by maba              #+#    #+#             */
/*   Updated: 2024/11/23 05:19:46 by ngoyat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pa_header.h"

int	check_pipe_syntax(t_token *current, int *expect_command, t_env_list *env_list)
{
	if (*expect_command || !current->next)
	{
		perror("Syntax error: unexpected token `|");
		ft_exit(env_list, 1);
		return (1);
	}
	*expect_command = 1;
	return (0);
}

int	check_redirect_syntax(t_token *current, t_env_list *env_list)
{
	if (!current->next || current->next->type != TOKEN_WORD)
	{
		printf("Syntax error: unexpected token `%s", current->typ);
		ft_exit(env_list, 1);
		return (1);
	}
	return (0);
}

void	update_expect_command(t_token *current, int *expect_command)
{
	if (current->type == TOKEN_WORD)
		*expect_command = 0;
}

int	handle_token(t_token *current, int *expect_command, t_env_list *env_list)
{
	int	error_code;

	if (current->type == TOKEN_PIPE)
		return (check_pipe_syntax(current, expect_command, env_list));
	if (current->type == TOKEN_REDIRECT_IN
		|| current->type == TOKEN_REDIRECT_OUT)
	{
		error_code = check_redirect_syntax(current, env_list);
		if (!error_code)
			*expect_command = 0;
		return (error_code);
	}
	update_expect_command(current, expect_command);
	return (0);
}

int	check_syntax_errors(t_token_list *token_list, t_env_list *env_list)
{
	t_token	*current;
	int		expect_command;
	int		error_code;

	current = token_list->head;
	expect_command = 1;
	while (current)
	{
		error_code = handle_token(current, &expect_command, env_list);
		if (error_code)
			return (error_code);
		current = current->next;
	}
	return (0);
}

// Function to check for unmatched quotes in the input
int	quote_check(const char *input, int i)
{
	int	single_quotes;
	int	double_quotes;

	single_quotes = 0;
	double_quotes = 0;
	while (input[i] != '\0')
	{
		if (input[i] == '\'')
			single_quotes++;
		else if (input[i] == '\"')
			double_quotes++;
		i++;
	}
	if (single_quotes % 2 != 0)
	{
		perror("Syntax error: unmatched single quotes");
		return (1);
	}
	if (double_quotes % 2 != 0)
	{
		perror("Syntax error: unmatched double quotes");
		return (1);
	}
	return (0);
}

// dorker valgrind --leak-check=full  --suppressions=readline.supp
// --show-leak-kinds=all --track-origins=yes --verbose ./shell

// char	*split_at_second_last(char *str, char delimiter)
// {
// 	int	len;
// 	int	count;
// 	int	split_index;

// 	len = strlen(str);
// 	count = 0;
// 	split_index = -1;
// 	// Traverse from the end to find the second-to-last occurrence
// 	for (int i = len - 1; i >= 0; i--)
// 	{
// 		if (str[i] == delimiter)
// 		{
// 			count++;
// 			if (count == 2)
// 			{
// 				split_index = i;
// 				break ;
// 			}
// 		}
// 	}
// 	// If the delimiter occurs fewer than 2 times, return NULL
// 	if (split_index == -1)
// 	{
// 		return (str);
// 	}
// 	Return pointer to the start of the substring after the split_index
// 	return (str + split_index);
// }

// void	ft_check_debug(char *input, t_env_list *env_list)
// {
// 	// Check if the input matches "debug"
// 	if (strcmp(input, "/debug") == 0)
// 	{
// 		// Toggle the debug field
// 		env_list->debug += 1;
// 		printf("Debug mode %s\n", (env_list->debug % 2 != 0) ? "ON" : "OFF");
// 	}
// }

// int	main(int argc, char **argv, char **envp)
// {
// 	char			*input;
// 	t_env_list		*env_list;
// 	t_commands_list	*cmd_list;
// 	t_token_list	*token_list;
// 	t_cmd_node		*current;
// 	static int		counter;

// 	//===================
// 	counter = 0;
// 	(void)current;
// 	(void)argc; // Marquer comme non utilisé
// 	(void)argv; // Marquer comme non utilisé
// 	setup_signal_handlers();
// 	disable_readline_signals();
// 	env_list = init_env_list(envp);
// 	if (!env_list)
// 	{
// 		perror("Failed to initialize environment list.\n");
// 		return (1);
// 	}
// 	while (1)
// 	{
// 		input = readline("minishell> ");
// 		ft_check_debug(input, env_list);
// 		if (!input)
// 		{
// 			printf("exit\n");
// 			if (input)
// 				free(input);
// 			break ;
// 		}
// 		if (!quote_check(input, 0))
// 			input = readline("minishell> ");
// 		add_history(input);
// 		token_list = tokenize_input(input, env_list);
// 		if (!token_list || check_syntax_errors(token_list, env_list) != 0)
// 		{
// 			free_token_list(token_list);
// 			free(input);
// 			continue ;
// 		}
// 		parse_and_group_commands(&cmd_list, &token_list, &env_list);
// 		if (env_list->debug % 2 != 0)
// 		{
// 			print_tokens(token_list);
// 			print_cmd_list(cmd_list);
// 			continue ;
// 		}
// 		current = cmd_list->head;
// 		handle_commands(cmd_list, env_list);
// 		free_token_list(token_list);
// 		free(input);
// 		counter++;
// 	}
// 	if (counter > 0)
// 	{
// 		rl_clear_history();
// 		if (env_list)
// 			free_env_list(env_list);
// 		if (cmd_list)
// 			free_cmd_list(cmd_list);
// 	}
// 	return (0);
// }

//==============================================================

void	ft_check_debug(char *input, t_env_list *env_list)
{
	if (input && strcmp(input, "/debug") == 0)
	{
		env_list->debug += 1;
		if (env_list->debug % 2 != 0)
			printf("Debug mode ON\n");
		else
			printf("Debug mode OFF\n");
	}
}
