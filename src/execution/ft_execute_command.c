

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

int	ft_split_len(char **split)
{
	if (!split || !(*split))
		return (0);
	return (1 + ft_split_len(split + 1));
}

static char	**merge_arrays(char **split_result, char **cmd)
{
	char	**new_cmd;
	int		split_len;
	int		cmd_len;
	int		total_len;
	int		i;

	if (!split_result || !cmd)
		return (NULL);
	split_len = ft_split_len(split_result);
	cmd_len = ft_split_len(cmd + 1);
	total_len = split_len + cmd_len;
	new_cmd = malloc(sizeof(char *) * (total_len + 1));
	if (!new_cmd)
		return (NULL);
	i = 0;
	while (i < split_len)
	{
		new_cmd[i] = ft_strdup(split_result[i]);
		i++;
	}
	while (i - split_len < cmd_len)
	{
		new_cmd[i] = ft_strdup(cmd[i - split_len + 1]);
		i++;
	}
	new_cmd[i] = NULL;
	return (new_cmd);
}

static void	split_first_argument(t_cmd_node *cmd)
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

void	split_command_and_flags(t_cmd_node *cmd)
{
	if (!cmd)
		return ;
	split_first_argument(cmd);
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
	handle_redirections(cmd, &in_fd, &out_fd);
	setup_file_descriptors(cmd, in_fd, out_fd);
	split_command_and_flags(cmd);
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
	envp = ft_copy_env(env_list);
	execve(cmd_path, cmd->cmd, envp);
	perror("execve");
	free(cmd_path);
	if (envp)
		free(envp);
	exit(EXIT_FAILURE);
}
