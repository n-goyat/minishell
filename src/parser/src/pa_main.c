/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pa_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoyat <ngoyat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 17:41:11 by ngoyat            #+#    #+#             */
/*   Updated: 2024/10/22 13:40:18 by ngoyat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pa_header.h"

t_token	*create_token(char *env_var)
{
	t_env	*new_node;
	char	*delimiter;

	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	new_node->key = ft_strndup(env_var, delimiter - env_var);
	new_node->value = ft_strdup(delimiter + 1);
	new_node->next = NULL;
	return (new_node);
}

t_env	*create_node_with_key_value(char *key, char *value)
{
	t_env	*new_node;

	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	new_node->key = ft_strdup(key);
	if (value != NULL)
		new_node->value = ft_strdup(value);
	else
		new_node->value = NULL;
	new_node->next = NULL;
	return (new_node);
}

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

t_env_list	*init_env_list(void)
{
	t_env_list	*env_list;

	env_list = malloc(sizeof(t_env_list));
	if (!env_list)
		return (NULL);
	env_list->head = NULL;
	env_list->tail = NULL;
	env_list->size = 0;
	return (env_list);
}

void	print_env_list(t_env *env_list)
{
	t_env	*temp;

	temp = env_list;
	while (temp != NULL)
	{
		printf("%s=%s\n", temp->key, temp->value);
		// printf("key: %s\n", tmp->key);
		// printf("value: %s\n", tmp->value);
		temp = temp->next;
	}
}

void	free_env_list(t_env *env_list)
{
	t_env	*temp;

	while (env_list != NULL)
	{
		temp = env_list;
		env_list = env_list->next;
		free(temp->key);
		free(temp->value);
		free(temp);
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
