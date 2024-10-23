

#include "../includes/pa_header.h"

/*

	* ft_execute_command() : Fonction centrale qui exécute les commandes externes en utilisant fork() et execve().
 *
 * Entrée : Un tableau de tokens correspondant à une commande.
 * Sortie : Le résultat de l'exécution.
 *
 */

/*

	* Fonction pour rechercher le chemin absolu d'une commande dans les répertoires spécifiés par PATH.
 */
char	*find_command_in_path(char *command, t_env *env_list)
{
	char	*path_env;
	char	**paths;
	char	*full_path;
	int		i;

	char *temp_path; // Temporary variable to avoid memory leaks
	path_env = get_env_value("PATH", env_list);
	if (path_env)
		printf("PATH environment variable: %s\n", path_env);
	else
		printf("PATH environment variable not found.\n");
	paths = ft_split(path_env, ':');
	i = 0;
	while (paths && paths[i])
	{
		temp_path = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin(temp_path, command);
		free(temp_path); // Free the intermediate path after joining
		printf("Checking path: %s\n", full_path);
		if (access(full_path, X_OK) == 0)
		{
			free_split(paths);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	free_split(paths);
	return (NULL); // Command not found
}

void	ft_execute_command(t_cmd_node *cmd, t_env *env_list)
{
	pid_t	pid;
	char	*cmd_path;
	char	**envp;

	envp = ft_copy_env(env_list);
	if (ft_strchr(cmd->cmd[0], '/') == NULL)
	{
		cmd_path = find_command_in_path(cmd->cmd[0], env_list);
	}
	else
	{
		cmd_path = ft_strdup(cmd->cmd[0]);
	}
	if (cmd_path)
	{
		printf("Resolved command path: %s\n", cmd_path);
		// Print the resolved command path
	}
	else
	{
		fprintf(stderr, "Command not found: %s\n", cmd->cmd[0]);
		free(envp);
		return ;
	}
	pid = fork();
	if (pid == 0)
	{
		if (cmd->files)
		{
			printf("Debug: Handling file redirection.\n");
			ft_handle_redirection(cmd->files);
		}
		if (cmd_path == NULL)
		{
			fprintf(stderr, "Command not found in PATH: %s\n", cmd->cmd[0]);
		}
		else
		{
			printf("Resolved command path in pipeline: %s\n", cmd_path);
		}
		if (execve(cmd_path, cmd->cmd, envp) == -1)
		{
			fprintf(stderr, "execve: Failed to execute command at %s\n",
				cmd_path);
			perror("execve");
			exit(EXIT_FAILURE);
		}
	}
	else if (pid < 0)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else
	{
		ft_wait_for_processes(pid);
	}
	free(cmd_path);
	free(envp);
}
