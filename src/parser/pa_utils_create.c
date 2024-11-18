/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pa_utils_create.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoyat <ngoyat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 23:51:08 by ngoyat            #+#    #+#             */
/*   Updated: 2024/11/18 23:51:11 by ngoyat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pa_header.h"

// Function to create a new token
t_token	*create_token(void)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->value = NULL;
	new_token->type = 0;
	new_token->next = NULL;
	return (new_token);
}

// Function to create a new cmd node
t_cmd_node	*create_cmd_node(char **cmd, t_files_list *files_list)
{
	t_cmd_node	*new_node;

	new_node = malloc(sizeof(t_cmd_node));
	if (!new_node)
		return (NULL);
	if (!cmd)
		new_node->cmd = NULL;
	else
		new_node->cmd = cmd;
	new_node->files = files_list;
	new_node->next = NULL;
	return (new_node);
}

// Function to create a new file node
t_file_node	*create_file_node(char *filename, int type)
{
	t_file_node	*new_node;

	new_node = malloc(sizeof(t_file_node));
	if (!new_node)
		return (NULL);
	new_node->filename = ft_strdup(filename);
	new_node->type = type;
	new_node->next = NULL;
	return (new_node);
}

// Function to create a new env node
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
	if (ft_strncmp(new_node->key, "SHLVL", ft_strlen(new_node->key)) == 0)
	{
		new_node->value = ft_itoa(ft_atoi(ft_strdup(delimiter + 1)) + 1);
		if (!(new_node->value))
			return (NULL);
	}
	else
		new_node->value = ft_strdup(delimiter + 1);
	new_node->next = NULL;
	return (new_node);
}

// Function to create a new env node with value
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
