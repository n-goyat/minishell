

#include "../includes/pa_header.h"

void	free_command_list(t_commands_list *cmd_list)
{
	t_cmd_node	*current;
	t_cmd_node	*temp;

	if (!cmd_list)
		return ;
	current = cmd_list->head;
	while (current)
	{
		temp = current;
		current = current->next;
		free(temp->cmd);
		free(temp->files); // Adjust if files list has its own free function
		free(temp);
	}
	free(cmd_list);
}

void	free_token_list(t_token_list *token_list)
{
	t_token	*current;
	t_token	*temp;

	if (!token_list)
		return ;
	current = token_list->head;
	while (current)
	{
		temp = current;
		current = current->next;
		free(temp->value);
		free(temp);
	}
	free(token_list);
}

int	main(int argc, char **argv, char **envp)
{
	t_env			*env_list;
	char			*input;
	t_commands_list	*cmd_list;
	t_token_list	*token_list;
	t_cmd_node		*current;

	(void)argc;
	(void)argv;
	env_list = init_env_list(envp);
	ft_handle_signals(); // Handle signals
	while (1)
	{
		cmd_list = init_commands_list();
		input = readline("minishell> ");
		if (!input)
			break ;
		if (*input == '\0')
		{
			free(input);
			continue ;
		}
		// env_list = init_env_list(envp);
		// Tokenize the input
		token_list = tokenize_input(input);
		// Parse the input
		parse_and_group_commands(&cmd_list, &token_list, env_list);
		// Print command list for debugging
		print_cmd_list(cmd_list);
		// Handle commands
		if (contains_pipe(token_list))
			ft_execute_pipeline(cmd_list->head, env_list);
		else
		{
			current = cmd_list->head;
			while (current)
			{
				if (is_builtin(current->cmd))
					ft_execute_builtin(current, env_list);
				else
					ft_execute_command(current, env_list);
				current = current->next;
			}
		}
		// Free the memory used by the input, environment, and command list
		free(input);
		free_env_list(env_list);
		free_command_list(cmd_list);
		free_token_list(token_list);
	}
	free_env_list(env_list); // Free environment memory
	return (0);
}
