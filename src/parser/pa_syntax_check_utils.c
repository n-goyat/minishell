/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pa_syntax_check_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoyat <ngoyat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 05:36:51 by ngoyat            #+#    #+#             */
/*   Updated: 2024/11/23 05:38:50 by ngoyat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pa_header.h"

int	check_pipe_syntax(t_token *current, int *expect_command,
		t_env_list *env_list)
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
