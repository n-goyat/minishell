
#include "../includes/pa_header.h"

// Function to add a token to the list
void	add_token(t_token_list *token_list, t_token *new_token)
{
	if (!new_token)
		return ;
	if (!token_list->head)
	{
		token_list->head = new_token;
		token_list->tail = new_token;
	}
	else
	{
		token_list->tail->next = new_token;
		token_list->tail = new_token;
	}
	token_list->size++;
}

// Function to add a command node to the list
void	add_cmd_node(t_commands_list *cmd_list, t_cmd_node *new_node)
{
	if (!new_node)
		return ;
	if (!cmd_list->head)
	{
		cmd_list->head = new_node;
		cmd_list->tail = new_node;
	}
	else
	{
		cmd_list->tail->next = new_node;
		cmd_list->tail = new_node;
	}
	cmd_list->size++;
}

// Function to add a file node to the list
void	add_file_node(t_files_list *files_list, t_file_node *new_file)
{
	if (!files_list || !new_file)
		return ;
	if (!files_list->head)
	{
		files_list->head = new_file;
		files_list->tail = new_file;
	}
	else
	{
		files_list->tail->next = new_file;
		files_list->tail = new_file;
	}
	files_list->size++;
}

// Function to add a env node to the list
void	add_node(t_env_list *env_list, t_env *new_node)
{
	if (!new_node)
		return ;
	if (!env_list->head)
	{
		env_list->head = new_node;
		env_list->tail = new_node;
	}
	else
	{
		env_list->tail->next = new_node;
		env_list->tail = new_node;
	}
	env_list->size++;
}
