/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_fonction.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maba <maba@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 12:26:31 by maba              #+#    #+#             */
/*   Updated: 2024/11/04 15:16:15 by maba             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pa_header.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (i < n && (s1[i] || s2[i]))
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] != '\0' && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

void free_split(char **split)
{
    int i = 0;

    if (!split)
        return;
    
    while (split[i])
    {
        free(split[i]);  // Libérer chaque sous-chaîne
        i++;
    }
    free(split);  // Libérer le tableau de pointeurs
}

void free_token_list(t_token_list *token_list)
{
    t_token *current_token = token_list->head;
    t_token *next_token;
    
    while (current_token)
    {
        next_token = current_token->next;
        free(current_token->value);  // Libère la valeur du token
        free(current_token);         // Libère le token lui-même
        current_token = next_token;
    }
    free(token_list);  // Libère la structure de la liste
}

