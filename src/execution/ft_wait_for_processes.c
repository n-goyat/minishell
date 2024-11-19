/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wait_for_processes.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maba <maba@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 14:57:12 by maba              #+#    #+#             */
/*   Updated: 2024/11/19 20:29:52 by maba             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pa_header.h"
#include "../includes/ex_header.h"

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
			fprintf(stderr, "Process exited with status %d\n", exit_status);
		}
	}
	else if (WIFSIGNALED(status))
	{
		signal = WTERMSIG(status);
		fprintf(stderr, "Process terminated by signal %d\n", signal);
	}
}
