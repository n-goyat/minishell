/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maba <maba@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 12:29:13 by maba              #+#    #+#             */
/*   Updated: 2024/03/11 21:19:42 by maba             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	size_t	len_s1;
	size_t	len_s2;
	char	*result;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	result = (char *)malloc((len_s1 + len_s2 + 1) * sizeof(char));
	if (result == NULL)
		return (NULL);
	i = -1;
	while (++i < len_s1)
		result[i] = s1[i];
	j = -1;
	while (++j < len_s2)
		result[i + j] = s2[j];
	result[i + j] = '\0';
	return (result);
}

// int	main(void)
// {
// 	// Exemple d'utilisation de ft_strjoin
// 	char const *prefix = "Hello, ";
// 	char const *suffix = "World!";
// 	char *joined = ft_strjoin(prefix, suffix); // Concaténer les deux chaînes
// 	printf("ft_strjoin: %s\n", joined);
// 	free(joined); // N'oubliez pas de libérer la mémoire allouée

// 	return (0);
// }