/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maba <maba@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 02:54:16 by maba              #+#    #+#             */
/*   Updated: 2024/11/20 02:56:47 by maba             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ex_header.h"
#include "../includes/pa_header.h"

void	update_or_add_variable(t_env_list *env_list, char *key, char *value,
		int is_append)
{
	t_env	*temp;
	char	*new_value;

	temp = env_list->head;
	while (temp)
	{
		if (ft_strcmp(temp->key, key) == 0)
		{
			if (is_append && value != NULL)
			{
				new_value = ft_strjoin(temp->value, value);
				free(temp->value);
				temp->value = new_value;
			}
			else if (value != NULL)
			{
				free(temp->value);
				temp->value = value;
			}
			free(key);
			return ;
		}
		temp = temp->next;
	}
	add_node(env_list, create_node_with_key_value(key, value));
}

void	concat_arguments(char **args, char **result)
{
	int		i;
	char	*temp;
	char	*arg;

	*result = ft_strdup(args[1]);
	i = 2;
	while (args[i])
	{
		temp = ft_strjoin(*result, " ");
		free(*result);
		arg = args[i];
		if ((arg[0] == '\'' || arg[0] == '"') && arg[ft_strlen(arg)
				- 1] == arg[0])
		{
			arg = ft_strndup(arg + 1, ft_strlen(arg) - 2);
			*result = ft_strjoin(temp, arg);
			free(arg);
		}
		else
			*result = ft_strjoin(temp, arg);
		free(temp);
		i++;
	}
}

void	remove_enclosing_quotes(char **str)
{
	size_t	len;
	char	*new_str;

	if (!str || !*str)
		return ;
	len = ft_strlen(*str);
	if (len > 1 && ((*str)[0] == '"' && (*str)[len - 1] == '"'))
	{
		new_str = ft_strndup((*str) + 1, len - 2);
		free(*str);
		*str = new_str;
	}
}

void	builtin_export(char **args, t_env_list *env_list)
{
	char	*key;
	char	*value;
	int		is_append;
	char	*concatenated_args;

	if (!args[1])
	{
		print_all_variables(env_list);
		return ;
	}
	concat_arguments(args, &concatenated_args);
	remove_enclosing_quotes(&concatenated_args);
	parse_key_value(concatenated_args, &key, &value, &is_append);
	free(concatenated_args);
	update_or_add_variable(env_list, key, value, is_append);
}
