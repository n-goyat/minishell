
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

void	free_cmd_node(t_cmd_node *cmd_node)
{
	int			i;
	t_file_node	*file;
	t_file_node	*next;

	if (!cmd_node)
		return ;
	if (cmd_node->cmd)
	{
		i = 0;
		while (cmd_node->cmd[i])
		{
			free(cmd_node->cmd[i]);
			i++;
		}
		free(cmd_node->cmd);
	}
	if (cmd_node->files)
	{
		file = cmd_node->files->head;
		while (file)
		{
			next = file->next;
			free(file->filename);
			free(file);
			file = next;
		}
		free(cmd_node->files);
	}
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

void	free_env_list(t_env_list *env_list)
{
	t_env	*temp;
	t_env	*current;

	current = env_list->head;
	while (current != NULL)
	{
		temp = current;
		current = current->next;
		free(temp->key);
		free(temp->value);
		free(temp);
	}
	free(env_list);
}
