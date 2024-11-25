/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gestion_environment.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoyat <ngoyat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 15:14:13 by maba              #+#    #+#             */
/*   Updated: 2024/11/25 04:14:19 by ngoyat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ex_header.h"
#include "../includes/pa_header.h"

static void	free_env_array(char **envp, int i)
{
	while (--i >= 0)
		free(envp[i]);
	free(envp);
}

static int	populate_env_array(char **envp, t_env *temp, int *i)
{
	char	*joined_str;

	while (temp)
	{
		joined_str = ft_strjoin(temp->key, "=");
		if (!joined_str)
		{
			free_env_array(envp, *i);
			return (0);
		}
		envp[*i] = ft_strjoin(joined_str, temp->value);
		free(joined_str);
		if (!envp[*i])
		{
			free_env_array(envp, *i);
			return (0);
		}
		temp = temp->next;
		(*i)++;
	}
	return (1);
}

char	**ft_copy_env(t_env_list *env_list)
{
	t_env	*temp;
	char	**envp;
	int		i;

	envp = (char **)malloc(sizeof(char *) * (env_list->size + 1));
	if (!envp)
		return (NULL);
	temp = env_list->head;
	i = 0;
	if (!populate_env_array(envp, temp, &i))
	{
		free(envp);
		return (NULL);
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
