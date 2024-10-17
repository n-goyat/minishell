/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pa_env_expander.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoyat <ngoyat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 14:33:07 by ngoyat            #+#    #+#             */
/*   Updated: 2024/10/17 15:20:43 by ngoyat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pa_header.h"

char	*get_env_value(char *var_name, t_env *env_list)
{
	while (env_list)
	{
		if (ft_strcmp(env_list->key, var_name) == 0)
			return (env_list->value);
		env_list = env_list->next;
	}
	return (NULL);
}

char	*expand_env_var(t_token **token, t_env *env_list)
{
	t_env	*current;
	char	*expanded_value;

	if ((*token)->type == TOKEN_SIN_QOTES)
		return (ft_strdup((*token)->value));
	if ((*token)->value[0] == '$')
	{
		current = env_list;
		while (current)
		{
			if (ft_strcmp(current->key, (*token)->value + 1) == 0)
			{
				expanded_value = ft_strdup(current->value);
				return (expanded_value);
			}
			current = current->next;
		}
	}
	return (ft_strdup((*token)->value));
}
