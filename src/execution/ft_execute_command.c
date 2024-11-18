

#include "../includes/pa_header.h"

// Retrieve the full path of a command by searching in PATH environment variable
char	*find_command_in_path(char *command, t_env_list *env_list)
{
	char	*path_env;
	char	**paths;
	char	*full_path;
	char	*temp;
	int		i;

	path_env = ft_get_env("PATH", env_list); // Retrieve PATH variable
	if (!path_env)
	{
		fprintf(stderr, "find_command_in_path: PATH is NULL\n");
		return (NULL);
	}
	paths = ft_split(path_env, ':');
	if (!paths)
	{
		fprintf(stderr, "find_command_in_path: ft_split failed\n");
		return (NULL);
	}
	i = 0;
	while (paths[i])
	{
		temp = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin(temp, command);
		free(temp);
		if (!full_path)
		{
			fprintf(stderr, "find_command_in_path: ft_strjoin failed\n");
			free_split(paths);
			return (NULL);
		}
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

// Determine the path of the command to execute
char	*get_command_path(t_cmd_node *cmd, t_env_list *env_list)
{
	char	*cmd_path;

	if (!cmd || !(cmd->cmd) || !(cmd->cmd[0]))
	{
		fprintf(stderr, "get_command_path: cmd or cmd->cmd is NULL\n");
		return (NULL);
	}
	if (cmd->cmd && ft_strchr(cmd->cmd[0], '/') == NULL)
	{
		cmd_path = find_command_in_path(cmd->cmd[0], env_list);
		if (!cmd_path)
			fprintf(stderr, "get_command_path: command not found in PATH\n");
	}
	else
	{
		cmd_path = ft_strdup(cmd->cmd[0]);
		if (!cmd_path)
			fprintf(stderr, "get_command_path: ft_strdup failed\n");
	}
	return (cmd_path);
}

void	split_command_and_flags(t_cmd_node *cmd)
{
	char	**split_result;

	if (!cmd || !cmd->cmd || !cmd->cmd[0])
		return ;
	// Split cmd->cmd[0] into separate tokens
	split_result = ft_split(cmd->cmd[0], ' ');
	// Free the original cmd->cmd array
	free_split(cmd->cmd);
	// Assign the new split array to cmd->cmd
	cmd->cmd = split_result;
}

void	execute_single_command(t_cmd_node *cmd, t_env_list *env_list)
{
	char	*cmd_path;
	char	**envp;
	int		in_fd;
	int		out_fd;

	envp = NULL;
	cmd_path = NULL;
	in_fd = STDIN_FILENO;
	out_fd = STDOUT_FILENO;
	// Handle redirections
	handle_redirections(cmd, &in_fd, &out_fd);
	setup_file_descriptors(cmd, in_fd, out_fd);
	// Split cmd->cmd[0] into command and arguments
	split_command_and_flags(cmd);
	// Retrieve command path
	if (cmd && cmd->cmd && cmd->cmd[0])
		cmd_path = get_command_path(cmd, env_list);
	else
		return ;
	if (!cmd_path)
	{
		fprintf(stderr, "Command not found: %s\n",
			cmd->cmd ? cmd->cmd[0] : "NULL");
		if (envp)
			free(envp);
		exit(127);
	}
	// Prepare environment and execute the command
	envp = ft_copy_env(env_list);
	execve(cmd_path, cmd->cmd, envp);
	perror("execve");
	free(cmd_path);
	if (envp)
		free(envp);
	exit(EXIT_FAILURE);
}
