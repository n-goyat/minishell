/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_command.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoyat <ngoyat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 04:44:46 by ngoyat            #+#    #+#             */
/*   Updated: 2024/11/25 04:13:44 by ngoyat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ex_header.h"
#include "../includes/pa_header.h"

void	handle_debug_command(t_cmd_node *cmd, t_env_list *env_list)
{
	if (cmd->cmd && cmd->cmd[0] && ft_strncmp(cmd->cmd[0], "/debug", 6) == 0)
	{
		env_list->debug++;
		ft_exit(env_list, 0);
		exit(0);
	}
}

void	*ft_exit(t_env_list *env_list, int exit_code)
{
	t_env	*current;

	current = env_list->head;
	if (env_list->head)
	{
		while (current)
		{
			if (strcmp(current->key, "?") == 0)
			{
				free(current->value);
				current->value = ft_itoa(exit_code);
			}
			current = current->next;
		}
	}
	return (0);
}

t_exec_data	prepare_exec_data(t_cmd_node *cmd, t_env_list *env_list)
{
	t_exec_data	data;

	data.envp = NULL;
	data.cmd_path = NULL;
	data.in_fd = STDIN_FILENO;
	data.out_fd = STDOUT_FILENO;
	handle_redirections(cmd, &data.in_fd, &data.out_fd);
	setup_file_descriptors(cmd, data.in_fd, data.out_fd);
	split_command_and_flags(cmd);
	if (cmd && cmd->cmd && cmd->cmd[0])
		data.cmd_path = get_command_path(cmd, env_list);
	return (data);
}

void	handle_command_not_found(const t_exec_data *data, t_cmd_node *cmd,
		t_env_list *env_list)
{
	(void)env_list;
	if (cmd->cmd && cmd->cmd[0] != NULL)
	{
		printf("minishell: %s: command not found\n", cmd->cmd[0]);
	}
	if (data->envp != NULL)
		free(data->envp);
}

void	execute_command(t_exec_data data, t_cmd_node *cmd, t_env_list *env_list)
{
	if (!data.cmd_path)
	{
		handle_command_not_found(&data, cmd, env_list);
		free(data.cmd_path);
		ft_exit(env_list, 127);
		exit(127);
	}
	data.envp = ft_copy_env(env_list);
	execve(data.cmd_path, cmd->cmd, data.envp);
	perror("execve");
	free(data.cmd_path);
	if (data.envp)
		free(data.envp);
	ft_exit(env_list, EXIT_FAILURE);
	exit(EXIT_FAILURE);
}
