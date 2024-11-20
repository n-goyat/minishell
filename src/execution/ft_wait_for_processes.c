/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wait_for_processes.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maba <maba@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 14:57:12 by maba              #+#    #+#             */
/*   Updated: 2024/11/20 14:45:50 by maba             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ex_header.h"
#include "../includes/pa_header.h"

void	ft_wait_for_processes(pid_t pid)
{
	int	status;
	int	exit_status;
	int	signal;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
	{
		exit_status = WEXITSTATUS(status);
		if (exit_status != 0)
		{
			ft_putstr_fd("Process exited with status\n", STDERR_FILENO);
		}
	}
	else if (WIFSIGNALED(status))
	{
		signal = WTERMSIG(status);
		ft_putstr_fd("Process terminated by signal\n", STDERR_FILENO);
	}
}
