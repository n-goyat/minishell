
#include "../includes/pa_header.h"

void	free_token_list(t_token_list *token_list)
{
	t_token	*current;
	t_token	*next;

	current = token_list->head;
	while (current)
	{
		next = current->next;
		free(current->value);
		free(current);
		current = next;
	}
	free(token_list);
}

void	free_cmd_args(char **cmd_args)
{
	int	i;

	if (cmd_args == NULL)
		return ;
	i = 0;
	while (cmd_args[i])
	{
		free(cmd_args[i]);
		i++;
	}
	free(cmd_args);
}

void	free_file_nodes(t_files_list *file_list)
{
	t_file_node	*file;
	t_file_node	*next;

	if (file_list == NULL)
		return ;
	file = file_list->head;
	while (file)
	{
		next = file->next;
		free(file->filename);
		free(file);
		file = next;
	}
	free(file_list);
}

void	free_cmd_node(t_cmd_node *cmd_node)
{
	if (cmd_node == NULL)
		return ;
	free_cmd_args(cmd_node->cmd);
	free_file_nodes(cmd_node->files);
	free(cmd_node);
}

void	free_cmd_list(t_commands_list *cmd_list)
{
	t_cmd_node	*current;
	t_cmd_node	*next;

	if (!cmd_list)
		return ;
	current = cmd_list->head;
	while (current)
	{
		next = current->next;
		free_cmd_node(current);
		current = next;
	}
	free(cmd_list);
}
