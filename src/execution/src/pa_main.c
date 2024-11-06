/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pa_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maba <maba@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 17:54:07 by maba              #+#    #+#             */
/*   Updated: 2024/11/01 23:07:50 by maba             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/pa_header.h"


t_env	*create_node(char *env_var)
{
	t_env	*new_node;
	char	*delimiter;

	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	delimiter = ft_strchr(env_var, '=');
	if (!delimiter)
		return (NULL);
	new_node->key = ft_strndup(env_var, delimiter - env_var);
	new_node->value = ft_strdup(delimiter + 1);
	new_node->next = NULL;
	return (new_node);
}

void	add_node(t_env **env_list, t_env *new_node)
{
	t_env	*temp;

	temp = *env_list;
	if (*env_list == NULL)
	{
		*env_list = new_node;
		return ;
	}
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = new_node;
}

t_env	*init_env_list(char **env)
{
	t_env	*env_list;
	t_env	*new_node;
	int		i;

	env_list = NULL;
	i = 0;
	while (env[i] != NULL)
	{
		new_node = create_node(env[i]);
		if (new_node != NULL)
			add_node(&env_list, new_node);
		i++;
	}
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