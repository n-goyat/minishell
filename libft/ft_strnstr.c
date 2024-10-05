/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maba <maba@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 11:55:54 by maba              #+#    #+#             */
/*   Updated: 2024/03/12 16:15:49 by maba             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	if (needle[0] == '\0')
		return ((char *)haystack);
	i = 0;
	while (haystack[i] != '\0' && i < len)
	{
		j = 0;
		while (haystack[i + j] == needle[j] && (i + j) < len
			&& needle[j] != '\0')
		{
			j++;
			if (needle[j] == '\0')
				return ((char *)(haystack + i));
		}
		i++;
	}
	return (NULL);
}

// int main() {
//     const char *haystack = "Hello world,
	// welcome to the world of C programming";
//     const char *needle = "world";
//     char *ptr = ft_strnstr(haystack, needle, 20);
//     if (ptr != NULL) {
//         printf("La sous-chaîne '%s' est trouvée à la position %ld.\n",
	// needle, ptr - haystack);
//     } else {
//         printf("La sous-chaîne '%s' n'est pas trouvée.\n", needle);
//     }
//     return (0);
// }