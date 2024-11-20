/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maba <maba@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 23:59:29 by ngoyat            #+#    #+#             */
/*   Updated: 2024/11/20 03:02:05 by maba             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ex_header.h"
#include "../includes/pa_header.h"

void	print_all_variables(t_env_list *env_list)
{
	t_env	*temp;

	temp = env_list->head;
	while (temp)
	{
		if (temp->key[0] == '?')
		{
			temp = temp->next;
			continue ;
		}
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putstr_fd(temp->key, STDOUT_FILENO);
		if (temp->value != NULL)
		{
			ft_putchar_fd('=', STDOUT_FILENO);
			ft_putchar_fd('"', STDOUT_FILENO);
			ft_putstr_fd(temp->value, STDOUT_FILENO);
			ft_putchar_fd('"', STDOUT_FILENO);
		}
		ft_putchar_fd('\n', STDOUT_FILENO);
		temp = temp->next;
	}
}

void	parse_key_value_with_delimiter(char *arg, char **key, char **value)
{
	char	*delimiter;
	char	quote_char;
	char	*end_quote;

	quote_char = '\0';
	delimiter = ft_strchr(arg, '=');
	*key = ft_strndup(arg, delimiter - arg);
	if (*(delimiter + 1) == '\'' || *(delimiter + 1) == '"')
	{
		quote_char = *(delimiter + 1);
		end_quote = ft_strchr(delimiter + 2, quote_char);
		if (end_quote)
			*value = ft_strndup(delimiter + 2, end_quote - (delimiter + 2));
		else
			*value = ft_strdup(delimiter + 1);
	}
	else
	{
		*value = ft_strdup(delimiter + 1);
	}
}

void	parse_key_value(char *arg, char **key, char **value, int *is_append)
{
	char	*delimiter;

	*is_append = 0;
	delimiter = ft_strchr(arg, '+');
	if (delimiter && *(delimiter + 1) == '=')
	{
		*is_append = 1;
		*key = ft_strndup(arg, delimiter - arg);
		*value = ft_strdup(delimiter + 2);
	}
	else
	{
		delimiter = ft_strchr(arg, '=');
		if (delimiter)
		{
			parse_key_value_with_delimiter(arg, key, value);
		}
		else
		{
			*key = ft_strdup(arg);
			*value = NULL;
		}
	}
}
