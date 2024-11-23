/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoyat <ngoyat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 04:05:51 by ngoyat            #+#    #+#             */
/*   Updated: 2024/11/23 05:11:10 by ngoyat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pa_header.h"

void	ft_debug_mode(t_token_list *token_list, t_commands_list *cmd_list)
{
	print_tokens(token_list);
	print_cmd_list(cmd_list);
	printf("\n\n");
}

int	ft_check_exit(char *input)
{
	if (!input)
	{
		printf("exit\n");
		if (input)
			free(input);
		return (1);
	}
	return (0);
}

void	ft_cleanup(t_env_list *env_list)
{
	rl_clear_history();
	if (env_list)
		free_env_list(env_list);
}

void	ft_cleanup_input(char *input, t_token_list *token_list)
{
	if (token_list)
		free_token_list(token_list);
	if (input)
		free(input);
}

int	ft_error_init_env(void)
{
	perror("Failed to initialize environment list.\n");
	return (1);
}

void	ft_main_loop(t_env_list *env_list, t_token_list *token_list,
		t_commands_list *cmd_list, char *input)
{
	setup_signal_handlers();
	disable_readline_signals();
	while (1)
	{
		input = readline("minishell> ");
		ft_check_debug(input, env_list);
		if (!input)
		{
			printf("exit\n");
			if (input)
				free(input);
			break ;
		}
		add_history(input);
		token_list = tokenize_input(input, env_list);
		if (!token_list && (quote_check(input, 0) != 0
				|| check_syntax_errors(token_list, env_list) != 0))
		{
			ft_exit(env_list, 1);
			ft_cleanup_input(input, token_list);
			continue ;
		}
		parse_and_group_commands(&cmd_list, &token_list, &env_list);
		if (env_list->debug % 2 != 0)
			ft_debug_mode(token_list, cmd_list);
		else
			handle_commands(cmd_list, env_list);
		ft_cleanup_input(input, token_list);
	}
	return ;
}

int	main(int argc, char **argv, char **envp)
{
	t_env_list		*env_list;
	t_token_list	*token_list;
	t_commands_list	*cmd_list;
	static int		counter;
	char			*input;

	input = NULL;
	token_list = NULL;
	cmd_list = NULL;
	(void)argc;
	(void)argv;
	counter = 0;
	env_list = init_env_list(envp);
	if (!env_list)
		return (ft_error_init_env());
	while (1)
		ft_main_loop(env_list, token_list, cmd_list, input);
	if (counter > 0)
		ft_cleanup(env_list);
	return (0);
}
