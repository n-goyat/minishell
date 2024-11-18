/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoyat <ngoyat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 23:58:32 by ngoyat            #+#    #+#             */
/*   Updated: 2024/11/18 23:58:34 by ngoyat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

// Helper to print command arguments
void	print_cmd_args(char **cmd)
{
	int	i;

	i = 0;
	printf("\nCommand:\n");
	while (cmd[i])
	{
		printf("Arg[%d]: %s\n", i, cmd[i]);
		i++;
	}
}

// Helper to print file nodes
void	print_cmd_files(t_files_list *files)
{
	t_file_node	*current_file;

	if (!files || !files->head)
		return ;
	printf("Files:\n");
	current_file = files->head;
	while (current_file)
	{
		printf("File: %s, Type: %d\n", current_file->filename,
			current_file->type);
		current_file = current_file->next;
	}
}

// Main function to iterate and print the command list
void	print_cmd_list(t_commands_list *cmd_list)
{
	t_cmd_node	*current_cmd;

	current_cmd = cmd_list->head;
	while (current_cmd)
	{
		print_cmd_args(current_cmd->cmd);
		print_cmd_files(current_cmd->files);
		current_cmd = current_cmd->next;
	}
}

void	print_env_list(t_env_list *env_list)
{
	t_env	*current_node;

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
