/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gestion_environment.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maba <maba@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 15:14:13 by maba              #+#    #+#             */
/*   Updated: 2024/10/24 17:36:22 by maba             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pa_header.h"

/**

	* ft_copy_env() : Crée une copie des variables d’environnement au démarrage du shell pour les manipuler.
 *
 * ft_get_env() : Récupère la valeur d’une variable d’environnement spécifique.
 * Entrée : Le nom de la variable.
 * Sortie : La valeur de la variable ou NULL si elle n'existe pas.
 */

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
		joined_str = ft_strjoin(temp->key, "=");       // Join "KEY="
		envp[i] = ft_strjoin(joined_str, temp->value); // Join "KEY=VALUE"
		free(joined_str);                             
			// Free intermediate string
		if (!envp[i])                                  // On failure, free all previous allocations
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

/**
 * Retrieves the value of a specific environment variable from env_list.
 *
 * @param key - The name of the environment variable to retrieve.
 * @param env_list - The linked list of environment variables.
 * @return The value of the environment variable, or NULL if not found.
 */
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
