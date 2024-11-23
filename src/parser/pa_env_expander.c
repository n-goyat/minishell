/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pa_env_expander.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoyat <ngoyat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 14:33:07 by ngoyat            #+#    #+#             */
/*   Updated: 2024/11/23 04:38:20 by ngoyat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pa_header.h"

// Search for an environment variable by name in the environment list
char	*get_env_value(char *env_name, t_env_list *env_list)
{
	t_env	*current;

	current = env_list->head;
	while (current)
	{
		if (ft_strcmp(current->key, env_name) == 0)
			return (ft_strdup(current->value));
		current = current->next;
	}
	return (NULL);
}

// Extract the variable name after a '$' in the token
char	*extract_env_name(const char *str, int *i)
{
	int		start;
	int		length;
	char	*env_name;

	start = *i + 1;
	length = 0;
	while (str[start + length] && (isalnum(str[start + length]) || str[start
				+ length] == '_' || str[start + length] == '?'))
		length++;
	env_name = ft_substr(str, start, length);
	*i = start + length;
	return (env_name);
}

// Expand a single '$' variable occurrence
char	*expand_single_variable(const char *str, int *i, t_env_list *env_list)
{
	char	*env_name;
	char	*expanded_value;

	env_name = extract_env_name(str, i);
	expanded_value = get_env_value(env_name, env_list);
	if (!expanded_value)
		expanded_value = ft_strdup("");
	free(env_name);
	return (expanded_value);
}

char	*expand_variable(char *value, int *i, t_env_list *env_list,
		char *result)
{
	char	*expanded;

	expanded = expand_single_variable(value, i, env_list);
	result = ft_strjoin_free(result, expanded);
	free(expanded);
	return (result);
}

// Main function to expand all environment variables in the token's value
char	*expand_env_var(t_token **token, t_env_list *env_list, int i)
{
	char	*result;

	if ((*token)->type == TOKEN_SIN_QOTES)
		return (quotes(token));
	result = ft_strdup("");
	while ((*token)->value[i] != '\0')
	{
		if ((*token)->value[i] == '\"' && (*token)->value[i + 1] == '\"')
			i += 2;
		else if ((*token)->value[i] == '$')
			result = expand_variable((*token)->value, &i, env_list, result);
		else
			result = append_character(result, (*token)->value[i++]);
	}
	return (result);
}
