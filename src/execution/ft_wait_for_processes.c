/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wait_for_processes.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoyat <ngoyat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 14:57:12 by maba              #+#    #+#             */
/*   Updated: 2024/11/23 04:56:41 by ngoyat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ex_header.h"
#include "../includes/pa_header.h"

void	ft_wait_for_processes(pid_t pid, t_env_list *env_list)
{
	int	status;
	int	signal;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
	{
		env_list->exit_code = WEXITSTATUS(status);
		ft_exit(env_list, env_list->exit_code);
	}
	else if (WIFSIGNALED(status))
	{
		signal = WTERMSIG(status);
		ft_putstr_fd("Process terminated by signal\n", STDERR_FILENO);
	}
}
