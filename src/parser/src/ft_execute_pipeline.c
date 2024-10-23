

#include "../includes/pa_header.h"

/**

	* ft_execute_pipeline() : Gère l'exécution des commandes connectées par des pipes (|),

	* en redirigeant la sortie de la première commande vers l'entrée de la suivante,
	et ainsi de suite.
 * Entrée : Liste de commandes séparées par des pipes.
 * Utilise : pipe(), dup2(), fork(), execve().
 */

void	ft_execute_pipeline(t_cmd_node *cmd, t_env *env_list)
{
	int			pipefd[2];
	pid_t		pid;
	t_cmd_node	*current_cmd;
	char		**envp;

	int prev_pipe_fd = -1; // File descriptor for previous read-end of pipe
	current_cmd = cmd;
	while (current_cmd)
	{
		printf("Debug: Preparing to execute command: %s\n",
			current_cmd->cmd[0]);
		// If there's a next command, create a pipe
		if (current_cmd->next)
		{
			if (pipe(pipefd) == -1)
			{
				perror("pipe");
				exit(EXIT_FAILURE);
			}
			printf("Debug: Pipe created, read-end: %d, write-end: %d\n",
				pipefd[0], pipefd[1]);
		}
		pid = fork();
		if (pid < 0)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		else if (pid == 0) // Child process
		{
			if (prev_pipe_fd != -1)
			{
				dup2(prev_pipe_fd, STDIN_FILENO);
				close(prev_pipe_fd);
				printf("Debug: Child process set input from prev_pipe_fd: %d\n",
					prev_pipe_fd);
			}
			// If there's a next command, set output to the current pipe
			if (current_cmd->next)
			{
				dup2(pipefd[1], STDOUT_FILENO);
				close(pipefd[0]); // Close read end of the pipe
				close(pipefd[1]);
				printf("Debug: Child process set output to pipefd[1]: %d\n",
					pipefd[1]);
			}
			// Handle file redirection if specified
			if (current_cmd->files)
			{
				ft_handle_redirection(current_cmd->files);
				printf("Debug: File redirection handled.\n");
			}
			// Execute the command
			envp = ft_copy_env(env_list);
			printf("Debug: Executing command: %s\n", current_cmd->cmd[0]);
			execve(current_cmd->cmd[0], current_cmd->cmd, envp);
			perror("execve"); // If execve fails, print error and exit
			exit(EXIT_FAILURE);
		}
		else // Parent process
		{
			// Close the write end of the current pipe
			if (current_cmd->next)
			{
				close(pipefd[1]);
				printf("Debug: Parent closed write-end of pipefd[1]: %d\n",
					pipefd[1]);
			}
			// Close the previous pipe's read end if it's open
			if (prev_pipe_fd != -1)
			{
				close(prev_pipe_fd);
				printf("Debug: Parent closed prev_pipe_fd: %d\n", prev_pipe_fd);
			}
			// Update previous pipe file descriptor to the current one
			if (current_cmd->next)
			{
				prev_pipe_fd = pipefd[0];
				printf("Debug: Updating prev_pipe_fd to: %d\n", prev_pipe_fd);
			}
		}
		// Move to the next command
		current_cmd = current_cmd->next;
	}
	// Wait for all child processes to finish
	while (wait(NULL) > 0)
	{
		printf("Debug: Waiting for child processes to finish.\n");
	}
}
