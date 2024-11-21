/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_command.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maba <maba@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 21:14:07 by maba              #+#    #+#             */
/*   Updated: 2024/11/20 14:46:16 by maba             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ex_header.h"
#include "../includes/pa_header.h"

// Determine the path of the command to execute
char	*get_command_path(t_cmd_node *cmd, t_env_list *env_list)
{
	char	*cmd_path;

	if (!cmd || !(cmd->cmd) || !(cmd->cmd[0]))
	{
		ft_putstr_fd("get_command_path: cmd or cmd->cmd is NULL\n",
			STDERR_FILENO);
		return (NULL);
	}
	if (cmd->cmd && ft_strchr(cmd->cmd[0], '/') == NULL)
	{
		cmd_path = find_command_in_path(cmd->cmd[0], env_list);
		if (!cmd_path)
			ft_putstr_fd("get_command_path: command not found in PATH\n",
				STDERR_FILENO);
	}
	else
	{
		cmd_path = ft_strdup(cmd->cmd[0]);
		if (!cmd_path)
			ft_putstr_fd("get_command_path: ft_strdup failed\n", STDERR_FILENO);
	}
	return (cmd_path);
}

static char	**merge_arrays(char **split_result, char **cmd)
{
	t_merge_data	data;

	if (!split_result || !cmd)
		return (NULL);
	data.split_len = ft_split_len(split_result);
	data.cmd_len = ft_split_len(cmd + 1);
	data.total_len = data.split_len + data.cmd_len;
	data.new_cmd = malloc(sizeof(char *) * (data.total_len + 1));
	if (!data.new_cmd)
		return (NULL);
	data.i = 0;
	while (data.i < data.split_len)
	{
		data.new_cmd[data.i] = ft_strdup(split_result[data.i]);
		data.i++;
	}
	while (data.i - data.split_len < data.cmd_len)
	{
		data.new_cmd[data.i] = ft_strdup(cmd[data.i - data.split_len + 1]);
		data.i++;
	}
	data.new_cmd[data.i] = NULL;
	return (data.new_cmd);
}

void	split_command_and_flags(t_cmd_node *cmd)
{
	char	**split_result;
	char	**new_cmd;

	if (!cmd || !cmd->cmd || !cmd->cmd[0] || !ft_strchr(cmd->cmd[0], ' '))
		return ;
	split_result = ft_split(cmd->cmd[0], ' ');
	if (!split_result)
		return ;
	new_cmd = merge_arrays(split_result, cmd->cmd);
	free_split(cmd->cmd);
	free_split(split_result);
	cmd->cmd = new_cmd;
}

static void	handle_command_not_found(const t_exec_data *data, t_cmd_node *cmd,
		t_env_list *env_list)
{
	if (cmd->cmd && cmd->cmd[0] != NULL)
		printf("minishell: %s: command not found\n", cmd->cmd[0]);
	else
		ft_putstr_fd("Command not found: NULL\n", STDERR_FILENO);
	if (data->envp != NULL)
		free(data->envp);
	ft_exit(env_list, 127);
}

void	execute_single_command(t_cmd_node *cmd, t_env_list *env_list)
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
	else
		return ;
	if (!data.cmd_path)
		handle_command_not_found(&data, cmd, env_list);
	data.envp = ft_copy_env(env_list);
	execve(data.cmd_path, cmd->cmd, data.envp);
	perror("execve");
	free(data.cmd_path);
	if (data.envp)
		free(data.envp);
	ft_exit(env_list, EXIT_FAILURE);
}

void	ft_exit(t_env_list *env_list, int exit_code)
{
	t_env	*current;

	current = env_list->head;
	while (current)
	{
		if (strcmp(current->key, "?") == 0)
			current->value = ft_strdup(ft_itoa(exit_code));
		return ;
		current = current->next;
	}
	exit(exit_code);
}
