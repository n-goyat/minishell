

#include "../includes/pa_header.h"

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
	// Calculate length of the variable name (alphanumeric or '_')
	while (str[start + length] && (isalnum(str[start + length]) || str[start
			+ length] == '_'))
		length++;
	env_name = ft_substr(str, start, length);
	*i = start + length; // Update index position
	return (env_name);
}

// Search for an environment variable by name in the environment list
char	*get_env_value(char *env_name, t_env *env_list)
{
	t_env	*current;

	current = env_list;
	while (current)
	{
		if (ft_strcmp(current->key, env_name) == 0)
			return (ft_strdup(current->value)); // Return a copy of the value
		current = current->next;
	}
	// If not found, return NULL (variable not in the environment)
	return (NULL);
}

// Expand a single '$' variable occurrence
char	*expand_single_variable(char *str, int *i, t_env *env_list)
{
	char	*env_name;
	char	*expanded_value;

	env_name = extract_env_name(str, i);
	expanded_value = get_env_value(env_name, env_list);
	// If variable is not found, return $NAME as is
	if (!expanded_value)
		expanded_value = ft_strjoin("$", env_name);
	free(env_name);
	return (expanded_value);
}

// Main function to expand all environment variables in the token's value
char	*expand_env_var(t_token **token, t_env *env_list)
{
	char	*result;
	char	tmp[2];
	int		i;
	char	*expanded;

	// If inside single quotes, return the value unchanged
	if ((*token)->type == TOKEN_SIN_QOTES)
		return (ft_strdup((*token)->value));
	result = ft_strdup(""); // Initialize result as an empty string
	i = 0;
	while ((*token)->value[i] != '\0')
	{
		if ((*token)->value[i] == '$')
		{
			// Expand the single variable and append it to the result
			expanded = expand_single_variable((*token)->value, &i, env_list);
			result = ft_strjoin_free(result, expanded);
			free(expanded);
		}
		else
		{
			// Append any non-variable character directly to the result
			tmp[0] = (*token)->value[i];
			tmp[1] = '\0';
			result = ft_strjoin_free(result, tmp);
			i++;
		}
	}
	return (result);
}
