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
			*value = ft_strdup(delimiter + 1);
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

// Main function: builtin_export
void	builtin_export(char **args, t_env_list *env_list)
{
	char	*key;
	char	*value;
	int		is_append;

	if (!args[1])
	{
		print_all_variables(env_list);
		return ;
	}
	parse_key_value(args[1], &key, &value, &is_append);
	update_or_add_variable(env_list, key, value, is_append);
}
