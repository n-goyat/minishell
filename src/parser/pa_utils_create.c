
#include "../includes/pa_header.h"

// Function to create a new token
t_token	*create_token(char *value, int type)
{
	t_token	*new_token;

	(void)value;
	(void)type;
	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->value = NULL;
	new_token->type = 0;
	new_token->next = NULL;
	return (new_token);
}

t_cmd_node	*create_cmd_node(char **cmd, t_files_list *files_list)
{
	t_cmd_node	*new_node;

	new_node = malloc(sizeof(t_cmd_node));
	if (!new_node)
		return (NULL);
	new_node->cmd = cmd;
	new_node->files = files_list;
	new_node->next = NULL;
	return (new_node);
}

t_file_node	*create_file_node(char *filename, int type)
{
	t_file_node	*new_node;

	new_node = malloc(sizeof(t_file_node));
	if (!new_node)
		return (NULL);
	new_node->filename = ft_strdup(filename);
	new_node->type = type;
	new_node->next = NULL;
	return (new_node);
}

t_env	*create_node(char *env_var)
{
	t_env	*new_node;
	char	*delimiter;

	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	delimiter = ft_strchr(env_var, '=');
	if (!delimiter)
		return (NULL);
	new_node->key = ft_strndup(env_var, delimiter - env_var);
	new_node->value = ft_strdup(delimiter + 1);
	new_node->next = NULL;
	return (new_node);
}

t_env	*create_node_with_key_value(char *key, char *value)
{
	t_env	*new_node;

	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	new_node->key = ft_strdup(key);
	if (value != NULL)
		new_node->value = ft_strdup(value);
	else
		new_node->value = NULL;
	new_node->next = NULL;
	return (new_node);
}
