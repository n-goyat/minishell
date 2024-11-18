#include "../includes/pa_header.h"

// Prints all environment variables in "declare -x" format
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

// Parses the key and value from the argument
void	parse_key_value(char *arg, char **key, char **value, int *is_append)
{
	char	*delimiter;
	char	quote_char;
	char	*end_quote;

	quote_char = '\0';
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
			*key = ft_strndup(arg, delimiter - arg);
			// Check for quoted value
			if (*(delimiter + 1) == '\'' || *(delimiter + 1) == '"')
			{
				quote_char = *(delimiter + 1);
				end_quote = ft_strchr(delimiter + 2, quote_char);
				if (end_quote)
				{
					*value = ft_strndup(delimiter + 2, end_quote - (delimiter
								+ 2));
				}
				else
				{
					*value = ft_strdup(delimiter + 1);
					// Fallback in case of malformed input
				}
			}
			else
			{
				*value = ft_strdup(delimiter + 1);
			}
		}
		else
		{
			*key = ft_strdup(arg);
			*value = NULL;
		}
	}
}

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

	*result = ft_strdup(args[1]); // Start with the first argument
	i = 2;
	while (args[i])
	{
		temp = ft_strjoin(*result, " "); // Add a space before the next argument
		free(*result);
		arg = args[i];
		if ((arg[0] == '\'' || arg[0] == '"') && arg[ft_strlen(arg)
				- 1] == arg[0]) // If quoted, trim quotes
		{
			arg = ft_strndup(arg + 1, ft_strlen(arg) - 2);
				// Copy without quotes
			*result = ft_strjoin(temp, arg);
			free(arg);
		}
		else
		{
			*result = ft_strjoin(temp, arg);
		}
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
		new_str = ft_strndup((*str) + 1, len - 2); // Remove enclosing quotes
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

	if (!args[1]) // If no arguments, print all variables
	{
		print_all_variables(env_list);
		return ;
	}
	concat_arguments(args, &concatenated_args);                  
		// Concatenate all arguments
	remove_enclosing_quotes(&concatenated_args);                 
		// Remove any outer quotes
	parse_key_value(concatenated_args, &key, &value, &is_append);
		// Parse key-value pair
	free(concatenated_args);
	update_or_add_variable(env_list, key, value, is_append);
		// Add or update variable
}
