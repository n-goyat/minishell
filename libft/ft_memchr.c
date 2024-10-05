/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maba <maba@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 11:57:24 by maba              #+#    #+#             */
/*   Updated: 2024/03/11 19:58:14 by maba             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t				i;
	const unsigned char	*str = s;
	unsigned char		occ;

	occ = c;
	i = 0;
	while (i < n)
	{
		if (str[i] == occ)
		{
			return ((void *)&str[i]);
		}
		i++;
	}
	return (0);
}

// int main() {
//     const char *str = "Hello, world!";
//     char target = 'w';
//     size_t n = 13;

//     // Recherche du caractère 'w' dans la chaîne str
//     void *result = ft_memchr(str, target, n);

//     if (result != NULL) {
//         printf("Le caractère '%c' a été trouvé à l'indice %ld.\n", target,
	// (char *)result - str);
//     } else {
//         printf("Le caractère '%c' n'a pas été trouvé dans la chaîne.\n",
	// target);
//     }

//     return (0);
// }