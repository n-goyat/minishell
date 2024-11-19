/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_pipeline.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maba <maba@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 14:57:02 by maba              #+#    #+#             */
/*   Updated: 2024/11/19 17:39:35 by maba             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ex_header.h"
#include "../includes/pa_header.h"

void	wait_for_all_processes(t_pipeline_data *data)
{
	int	i;

	i = 0;
	while (i < data->cmd_index)
	{
		waitpid(data->pids[i], NULL, 0);
		i++;
	}
}

void	execute_pipeline(t_commands_list *cmd_list, t_env_list *env_list)
{
	t_pipeline_data	data;

	initialize_pipeline(&data, cmd_list);
	while (data.current != NULL)
	{
		data.is_last_cmd = (data.current->next == NULL);
		setup_pipe(&data);
		fork_and_execute_command(&data, env_list);
		manage_descriptors(&data);
		data.current = data.current->next;
	}
	wait_for_all_processes(&data);
}

void	execute_individual_command(t_cmd_node *current, t_env_list *env_list)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return ;
	}
	if (pid == 0)
	{
		execute_single_command(current, env_list);
		exit(0);
	}
	else
		ft_wait_for_processes(pid);
}

void	handle_commands(t_commands_list *cmd_list, t_env_list *env_list)
{
	t_cmd_node	*current;

	current = cmd_list->head;
	if (cmd_list->size > 1)
		execute_pipeline(cmd_list, env_list);
	else
	{
		while (current != NULL)
		{
			if (is_builtin(current->cmd))
				ft_execute_builtin(current, env_list);
			else
				execute_individual_command(current, env_list);
			current = current->next;
		}
	}
}
