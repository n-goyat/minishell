

#include "../includes/pa_header.h"

// Correction de `find_command_in_path`
char	*find_command_in_path(char *command, t_env *env_list)
{
	char	*path_env;
	char	**paths;
	char	*full_path;
	char	*temp;
	int		i;

	path_env = get_env_value("PATH", env_list);
	paths = ft_split(path_env, ':');
	i = 0;
	if (!paths)
		return (NULL);
	while (paths[i])
	{
		temp = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin(temp, command);
		free(temp);
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
	char	*cmd_path;

	if (ft_strchr(cmd->cmd[0], '/') == NULL)
	{
		cmd_path = find_command_in_path(cmd->cmd[0], env_list);
		if (!cmd_path)
			return (NULL);
	}
	else
	{
		cmd_path = ft_strdup(cmd->cmd[0]);
	}
	return (cmd_path);
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

void	ft_execute_command(t_cmd_node *cmd, t_env_list *env_list)
{
	pid_t	pid;
	char	*cmd_path;
	char	**envp;
	int		in_fd;
	int		out_fd;

	in_fd = 0;
	out_fd = 1;
	envp = ft_copy_env(env_list);
	cmd_path = get_command_path(cmd, env_list);
	
	if (!cmd_path)
	{
		fprintf(stderr, "Command not found: %s\n", cmd->cmd[0]);
		free(envp);
		return ;
	}
	if (ft_check_files(cmd->files, &in_fd, &out_fd) != 0)
	{
		perror("Redirection error");
        free(cmd_path);
        free(envp);
        return ;
	}
	pid = fork();
	if (pid == 0)
	{
		ft_handle_redirections(cmd, &in_fd, &out_fd, cmd_path, envp);
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
	if (in_fd > 0)
		close(in_fd);
	if (out_fd > 1)
		close(out_fd);
}
