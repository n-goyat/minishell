/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pa_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoyat <ngoyat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 23:57:51 by ngoyat            #+#    #+#             */
/*   Updated: 2024/11/18 23:57:55 by ngoyat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pa_header.h"

t_files_list	*init_files_list(void)
{
	t_files_list	*files_list;

	files_list = malloc(sizeof(t_files_list));
	if (!files_list)
		return (NULL);
	files_list->head = NULL;
	files_list->tail = NULL;
	files_list->size = 0;
	return (files_list);
}

t_commands_list	*init_commands_list(void)
{
	t_commands_list	*cmd_list;

	cmd_list = malloc(sizeof(t_commands_list));
	if (!cmd_list)
		return (NULL);
	cmd_list->head = NULL;
	cmd_list->tail = NULL;
	cmd_list->size = 0;
	return (cmd_list);
}

t_token_list	*init_token_list(void)
{
	t_token_list	*token_list;

	token_list = malloc(sizeof(t_token_list));
	if (!token_list)
		return (NULL);
	token_list->head = NULL;
	token_list->tail = NULL;
	token_list->size = 0;
	return (token_list);
}

void	init_env_list_from_envp(t_env_list *env_list, char **envp)
{
	int		i;
	t_env	*new_node;

	i = 0;
	while (envp[i])
	{
		new_node = create_node(envp[i]);
		if (new_node)
		{
			add_node(env_list, new_node);
		}
		i++;
	}
	new_node = create_exit_code_node();
	if (new_node)
	{
		add_node(env_list, new_node);
	}
}

t_env_list	*init_env_list(char **envp)
{
	t_env_list	*env_list;

	env_list = malloc(sizeof(t_env_list));
	if (!env_list)
		return (NULL);
	env_list->head = NULL;
	env_list->tail = NULL;
	env_list->size = 0;
	init_env_list_from_envp(env_list, envp);
	return (env_list);
}
