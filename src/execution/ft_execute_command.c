

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
static char	*get_command_path(t_cmd_node *cmd, t_env_list *env_list)
{
	char	*cmd_path;

	if (ft_strchr(cmd->cmd[0], '/') == NULL) // Command without path
		cmd_path = find_command_in_path(cmd->cmd[0], env_list);
	else // Command includes a path
		cmd_path = ft_strdup(cmd->cmd[0]);
	return (cmd_path);
}

// Execute a command using execve and handle errors
void	execute_command(t_cmd_node *cmd, char *cmd_path, char **envp)
{
	if (execve(cmd_path, cmd->cmd, envp) == -1)
	{
		perror("execve");
		free(cmd_path);
		free(envp);
		exit(EXIT_FAILURE);
	}
}

void execute_single_command(t_cmd_node *cmd, t_env_list *env_list) 
{
    char *cmd_path = get_command_path(cmd, env_list);
    char **envp = ft_copy_env(env_list);
    if (!cmd_path) 
    {
        fprintf(stderr, "Command not found: %s\n", cmd->cmd[0]);
        free(envp);
        return;
    }
    execve(cmd_path, cmd->cmd, envp);
    perror("execve");
    free(cmd_path);
    free(envp);
    exit(EXIT_FAILURE);
}


void fork_and_execute(t_cmd_node *cmd, t_env_list *env_list, int in_fd, int out_fd) 
{
    pid_t pid = fork();
    if (pid == -1) 
    {
        perror("fork");
        exit(EXIT_FAILURE);
    } 
    else if (pid == 0) 
    {
		ft_handle_redirections(cmd, &in_fd, &out_fd, NULL, NULL);
        execute_single_command(cmd, env_list);
    } 
    else 
        ft_wait_for_processes(pid);
}

void ft_execute_command(t_cmd_node *cmd, t_env_list *env_list) 
{
    int in_fd = 0;
    int out_fd = 1;
    if (ft_check_files(cmd->files, &in_fd, &out_fd) != 0) 
    {
        perror("Redirection error");
        return;
    }
    fork_and_execute(cmd, env_list, in_fd, out_fd);
    if (in_fd > 0)
        close(in_fd);
    if (out_fd > 1)
        close(out_fd);
}
