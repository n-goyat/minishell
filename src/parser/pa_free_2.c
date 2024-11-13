
#include "../includes/pa_header.h"

void	free_env_list(t_env_list *env_list)
{
	t_env	*temp;
	t_env	*current;

	current = env_list->head;
	while (current != NULL)
	{
		temp = current;
		current = current->next;
		free(temp->key);
		free(temp->value);
		free(temp);
	}
	free(env_list);
}
