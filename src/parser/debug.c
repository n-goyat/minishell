
#include "../includes/pa_header.h"

// Function to print tokens (for testing)
void	print_tokens(t_token_list *token_list)
{
	t_token	*current_token;

	if (!token_list || !token_list->head)
	{
		printf("Token list is empty.\n");
		return ;
	}
	current_token = token_list->head;
	while (current_token != NULL)
	{
		printf("Token: %s, Type: %d\n", current_token->value,
			current_token->type);
		current_token = current_token->next;
	}
}

void	print_cmd_list(t_commands_list *cmd_list)
{
	t_cmd_node	*current_cmd;
	t_file_node	*current_file;
	int			i;

	current_cmd = cmd_list->head;
	while (current_cmd)
	{
		printf("\nCommand:\n");
		for (i = 0; current_cmd->cmd[i]; i++)
			printf("Arg[%d]: %s\n", i, current_cmd->cmd[i]);
		if (current_cmd->files && current_cmd->files->head)
		{
			printf("Files:\n");
			current_file = current_cmd->files->head;
			while (current_file)
			{
				printf("File: %s, Type: %d\n", current_file->filename,
					current_file->type);
				current_file = current_file->next;
			}
		}
		current_cmd = current_cmd->next;
	}
}

void	print_env_list(t_env_list *env_list)
{
	t_env *current_node;

	if (!env_list || !env_list->head)
	{
		printf("Token list is empty.\n");
		return ;
	}
	current_node = env_list->head;
	while (current_node != NULL)
	{
		printf("%s=%s\n", current_node->key, current_node->value);
		current_node = current_node->next;
	}
}