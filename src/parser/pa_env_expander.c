/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pa_env_expander.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maba <maba@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 14:33:07 by ngoyat            #+#    #+#             */
/*   Updated: 2024/10/21 15:49:12 by maba             ###   ########.fr       */
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

// Utility function to concatenate two strings and free the first one
char	*ft_strjoin_free(char *s1, const char *s2)
{
	char	*result;
	size_t	len1;
	size_t	len2;

	if (!s1 || !s2)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	result = malloc(len1 + len2 + 1);
	if (!result)
	{
		free(s1);
		return (NULL);
	}
	ft_memcpy(result, s1, len1);
	ft_memcpy(result + len1, s2, len2 + 1);
	free(s1);
	return (result);
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
			+ length] == '_'))
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

char	**split_and_free(char *str, char *delim)
{
	char	**result;

	result = ft_split(str, *delim);
	free(str);
	return (result);
}
// Main function to expand all environment variables in the token's value
char	*expand_env_var(t_token **token, t_env_list *env_list, int i)
{
	char	*result;
	char	tmp[2];
	char	*expanded;

	// If it's a single quote, don't expand
	if ((*token)->type == TOKEN_SIN_QOTES)
		return (ft_strdup((*token)->value));
	// Initialize result string
	result = ft_strdup("");
	while ((*token)->value[i] != '\0')
	{
		// Handle empty quotes specifically ("" should be treated as empty string)
		if ((*token)->value[i] == '\"' && (*token)->value[i + 1] == '\"')
		{
			// Skip the empty quotes and add an empty string
			i += 2;
			continue ; // Skip this pair of empty quotes
		}
		// Handle variable expansion when '$' is found
		if ((*token)->value[i] == '$')
		{
			expanded = expand_single_variable((*token)->value, &i, env_list);
			result = ft_strjoin_free(result, expanded);
			free(expanded);
		}
		else
		{
			// Just append the character to the result
			tmp[0] = (*token)->value[i];
			tmp[1] = '\0';
			result = ft_strjoin_free(result, tmp);
			i++;
		}
	}
	// Return the expanded result
	return (result);
}

// Helper function to check if the current position is inside single quotes
int	inside_single_quotes(const char *str, int pos)
{
	int	i;
	int	quote_count;

	i = 0;
	quote_count = 0;
	// Loop through the string up to the given position to count single quotes
	while (i < pos)
	{
		if (str[i] == '\'')
			quote_count++;
		i++;
	}
	// If there's an odd number of single quotes, we're inside a pair
	return (quote_count % 2 != 0);
}
