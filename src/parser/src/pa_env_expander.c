

#include "../includes/pa_header.h"

// Search for an environment variable by name in the environment list
char	*get_env_value(char *env_name, t_env *env_list)
{
	t_env	*current;

	current = env_list;
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
char	*expand_single_variable(const char *str, int *i, t_env *env_list)
{
	char	*env_name;
	char	*expanded_value;

	env_name = extract_env_name(str, i);
	expanded_value = get_env_value(env_name, env_list);
	if (!expanded_value)
		expanded_value = ft_strjoin("$", env_name);
	free(env_name);
	return (expanded_value);
}

// Function to update the state of quotes
void	update_quote_state(char c, int *in_sin_q, int *in_d_q)
{
	if (c == '\'' && !(*in_d_q))
		*in_sin_q = !(*in_sin_q);
	else if (c == '"' && !(*in_sin_q))
		*in_d_q = !(*in_d_q);
}

// Function to handle variable expansion based on context
char	*process_exp(const char *str, int *i, int in_sin_q, t_env *env_list)
{
	if (str[*i] == '$' && !in_sin_q)
	{
		return (expand_single_variable(str, i, env_list));
	}
	return (NULL);
}

// Function to handle the expansion of environment variables within a token
char	*expander(t_token **token, t_env *env_list, int *in_sin_q, int *in_d_q,
		int i)
{
	char	*result;
	char	tmp[2];
	char	*expanded;

	result = ft_strdup("");
	while ((*token)->value[i] != '\0')
	{
		if ((*token)->value[i] == '\'' || (*token)->value[i] == '"')
			update_quote_state((*token)->value[i], in_sin_q, in_d_q);
		else
		{
			expanded = process_exp((*token)->value, &i, *in_sin_q, env_list);
			if (expanded)
			{
				result = ft_strjoin_free(result, expanded);
				free(expanded);
				continue ;
			}
			tmp[0] = (*token)->value[i];
			tmp[1] = '\0';
			result = ft_strjoin_free(result, tmp);
		}
		i++;
	}
	return (result);
}

// Main function to expand all environment variables in the token's value
char	*expand_env_var(t_token **token, t_env *env_list)
{
	char	*result;
	int		in_sin_q;
	int		in_d_q;

	if ((*token)->type == TOKEN_SIN_QOTES)
		return (ft_strdup((*token)->value));
	in_sin_q = 0;
	in_d_q = 0;
	result = expander(token, env_list, &in_sin_q, &in_d_q, 0);
	return (result);
}
