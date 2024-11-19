/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_pipeline_bis.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maba <maba@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 17:38:53 by maba              #+#    #+#             */
/*   Updated: 2024/11/19 17:40:34 by maba             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ex_header.h"
#include "../includes/pa_header.h"

void	initialize_pipeline(t_pipeline_data *data, t_commands_list *cmd_list)
{
	data->current = cmd_list->head;
	data->in_fd = STDIN_FILENO;
	data->cmd_index = 0;
}

void	setup_pipe(t_pipeline_data *data)
{
	if (!data->is_last_cmd && pipe(data->pipefd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
}

void	manage_descriptors(t_pipeline_data *data)
{
	if (data->in_fd != STDIN_FILENO)
		close(data->in_fd);
	if (!data->is_last_cmd)
		close(data->pipefd[1]);
	data->in_fd = data->pipefd[0];
}

void	setup_child_descriptors(t_pipeline_data *data)
{
	if (data->in_fd != STDIN_FILENO)
	{
		dup2(data->in_fd, STDIN_FILENO);
		close(data->in_fd);
	}
	if (!data->is_last_cmd)
	{
		dup2(data->pipefd[1], STDOUT_FILENO);
		close(data->pipefd[1]);
	}
	close(data->pipefd[0]);
}

void	fork_and_execute_command(t_pipeline_data *data, t_env_list *env_list)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		setup_child_descriptors(data);
		execute_single_command(data->current, env_list);
		exit(0);
	}
	else
	{
		data->pids[data->cmd_index++] = pid;
	}
}
