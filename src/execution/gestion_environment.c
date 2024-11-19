/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gestion_environment.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maba <maba@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 15:14:13 by maba              #+#    #+#             */
/*   Updated: 2024/11/19 20:30:05 by maba             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pa_header.h"
#include "../includes/ex_header.h"

char	**ft_copy_env(t_env_list *env_list)
{
	int		i;
	t_env	*temp;
	char	*joined_str;
	char	**envp;

	envp = (char **)malloc(sizeof(char *) * (env_list->size + 1));
	if (!envp)
		return (NULL);
	temp = env_list->head;
	i = 0;
	while (temp)
	{
		joined_str = ft_strjoin(temp->key, "=");
		envp[i] = ft_strjoin(joined_str, temp->value);
		free(joined_str);
		if (!envp[i])
		{
			while (--i >= 0)
				free(envp[i]);
			free(envp);
			return (NULL);
		}
		temp = temp->next;
		i++;
	}
	envp[i] = NULL;
	return (envp);
}

char	*ft_get_env(char *key, t_env_list *env_list)
{
	t_env	*temp;

	temp = env_list->head;
	while (temp)
	{
		if (ft_strcmp(temp->key, key) == 0)
			return (temp->value);
		temp = temp->next;
	}
	return (NULL);
}
