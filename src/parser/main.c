/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoyat <ngoyat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 04:05:51 by ngoyat            #+#    #+#             */
/*   Updated: 2024/11/25 04:59:05 by ngoyat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pa_header.h"

void	main_helper(t_token_list *token_list, t_commands_list *cmd_list,
		t_env_list *env_list)
{
	if (env_list->debug % 2 != 0)
	{
		ft_debug_mode(token_list, cmd_list);
		handle_commands(cmd_list, env_list);
	}
	else
		handle_commands(cmd_list, env_list);
}

void	handle_null_input(char *input)
{
	if (!input)
	{
		printf("exit\n");
		free(input);
	}
}
// char	*prompt;
// prompt = msh_prompt(env_list);
// free(prompt);

int	ft_main_loop(t_env_list *env_list, t_token_list *token_list,
		t_commands_list *cmd_list, char *input)
{
	while (1)
	{
		input = readline(GR "minishell$ " CY);
		ft_check_debug(input, env_list);
		handle_null_input(input);
		if (!input)
			break ;
		add_history(input);
		token_list = tokenize_input(input, env_list);
		if (!token_list && (quote_check(input, 0) != 0
				|| check_syntax_errors(token_list, env_list) != 0))
		{
			ft_exit(env_list, 1);
			ft_cleanup_input(input, token_list, cmd_list);
			continue ;
		}
		parse_and_group_commands(&cmd_list, &token_list, &env_list);
		main_helper(token_list, cmd_list, env_list);
		ft_cleanup_input(input, token_list, cmd_list);
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_env_list		*env_list;
	t_token_list	*token_list;
	t_commands_list	*cmd_list;
	char			*input;

	input = NULL;
	token_list = NULL;
	cmd_list = NULL;
	(void)argc;
	(void)argv;
	setup_signal_handlers();
	disable_readline_signals();
	env_list = init_env_list(envp);
	if (!env_list)
		return (ft_error_init_env());
	while (1)
	{
		if (!ft_main_loop(env_list, token_list, cmd_list, input))
			break ;
	}
	ft_cleanup(env_list);
	return (0);
}
