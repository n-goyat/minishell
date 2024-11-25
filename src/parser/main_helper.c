/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoyat <ngoyat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 05:33:55 by ngoyat            #+#    #+#             */
/*   Updated: 2024/11/25 04:15:47 by ngoyat           ###   ########.fr       */
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

void	ft_cleanup_input(char *input, t_token_list *token_list,
		t_commands_list *cmd_list)
{
	if (token_list)
		free_token_list(token_list);
	if (cmd_list)
		free_cmd_list(cmd_list);
	if (input)
		free(input);
}

int	ft_error_init_env(void)
{
	perror("Failed to initialize environment list.\n");
	return (1);
}
