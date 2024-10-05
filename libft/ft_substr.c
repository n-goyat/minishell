/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maba <maba@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 19:17:48 by maba              #+#    #+#             */
/*   Updated: 2024/03/12 12:41:21 by maba             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	s_len;
	size_t	count;
	char	*sub_str;

	if (s == NULL)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len)
		return (ft_strdup(""));
	if (len > s_len - start)
		len = s_len - start;
	sub_str = (char *)malloc((len + 1) * sizeof(char));
	if (sub_str == NULL)
		return (NULL);
	count = 0;
	while (count < len)
	{
		sub_str[count] = s[start + count];
		count++;
	}
	sub_str[count] = '\0';
	return (sub_str);
}

// int main()
// {
//     // Exemple d'utilisation de ft_substr
//     char const *str = "Hello, World!";
//     char *substr = ft_substr(str, 2, 5);
// Extraire "World" à partir de l'indice 7 avec une longueur de 5
//     printf("ft_substr: %s\n", substr);
//     free(substr); // N'oubliez pas de libérer la mémoire allouée
//     return (0);
// }
