
#include "../includes/pa_header.h"

t_env	*create_exit_code_node(void)
{
	t_env	*new_node;

	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	new_node->key = ft_strdup("?");
	new_node->value = ft_strdup("0");
	new_node->next = NULL;
	return (new_node);
}
