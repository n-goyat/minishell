

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
		return (NULL);
	paths = ft_split(path_env, ':');
	if (!paths)
		return (NULL);
	i = 0;
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

// Determine the path of the command to execute
char	*get_command_path(t_cmd_node *cmd, t_env_list *env_list)
{
	char	*cmd_path;

	if (ft_strchr(cmd->cmd[0], '/') == NULL)
		cmd_path = find_command_in_path(cmd->cmd[0], env_list);
	else 
		cmd_path = ft_strdup(cmd->cmd[0]);
	return (cmd_path);
}

void execute_single_command(t_cmd_node *cmd, t_env_list *env_list) 
{
	char *cmd_path;
	char **envp;
    int in_fd = STDIN_FILENO;
    int out_fd = STDOUT_FILENO;

    handle_redirections(cmd, &in_fd, &out_fd);
    setup_file_descriptors(cmd, in_fd, out_fd);
    cmd_path = get_command_path(cmd, env_list);
    envp = ft_copy_env(env_list);

    if (!cmd_path) 
    {
        fprintf(stderr, "Command not found: %s\n", cmd->cmd[0]);
        free(envp);
        exit(127);
    }

    execve(cmd_path, cmd->cmd, envp);
    perror("execve");
    free(cmd_path);
    free(envp);
    exit(EXIT_FAILURE);
}
