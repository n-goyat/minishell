/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_command.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maba <maba@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 14:56:55 by maba              #+#    #+#             */
/*   Updated: 2024/10/25 14:52:11 by maba             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pa_header.h"

char	*find_command_in_path(char *command, t_env *env_list)
{
	char	*path_env;
	char	**paths;
	char	*full_path;
	int		i;

	path_env = get_env_value("PATH", env_list);
	paths = ft_split(path_env, ':');
	i = 0;
	// Boucle pour essayer chaque chemin dans PATH
	while (paths && paths[i])
	{
		full_path = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin(full_path, command);
		if (access(full_path, X_OK) == 0)
		{
			free_split(paths);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	free_split(paths);
	return (NULL);
}

static char	*get_command_path(t_cmd_node *cmd, t_env *env_list)
{
	if (ft_strchr(cmd->cmd[0], '/') == NULL)
		return (find_command_in_path(cmd->cmd[0], env_list));
	return (ft_strdup(cmd->cmd[0]));
}

static void	execute_command(t_cmd_node *cmd, char *cmd_path, char **envp)
{
	if (execve(cmd_path, cmd->cmd, envp) == -1)
	{
		perror("execve");
		free(cmd_path);
		free(envp);
		exit(EXIT_FAILURE);
	}
}

void	ft_execute_command(t_cmd_node *cmd, t_env *env_list)
{
	pid_t	pid;
	char	*cmd_path;
	char	**envp;
	int		in_fd = 0, out_fd;

	// if (return_val of check_file == WRONG)
	// {
	// 	print_msg ......
	// }
	// else
	// {

	// }
	envp = ft_copy_env(env_list);
	in_fd = 0, out_fd = 1;
	cmd_path = get_command_path(cmd, env_list);
	ft_handle_redirections(cmd, &in_fd, &out_fd, cmd_path, envp);
	if (!cmd_path)
	{
		fprintf(stderr, "Command not found: %s\n", cmd->cmd[0]);
		free(envp);
		return ;
	}
	pid = fork();
	if (pid == 0)
	{
		execute_command(cmd, cmd_path, envp);
	}
	else if (pid < 0)
	{
		perror("fork");
		free(cmd_path);
		free(envp);
		exit(EXIT_FAILURE);
	}
	else
		ft_wait_for_processes(pid);
	free(cmd_path);
	free(envp);
}
