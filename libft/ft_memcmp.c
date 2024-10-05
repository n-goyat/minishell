/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maba <maba@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 11:54:33 by maba              #+#    #+#             */
/*   Updated: 2024/03/12 17:51:52 by maba             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t				i;
	const unsigned char	*str1;
	const unsigned char	*str2;

	str1 = (const unsigned char *)s1;
	str2 = (const unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if (str1[i] != str2[i])
			return (str1[i] - str2[i]);
		i++;
	}
	return (0);
}

// int main() {
//     const char *str1 = "Hello7";
//     const char *str2 = "Helyo";
//     size_t n = 8; // Nombre d'octets à comparer

//     // Comparaison des 5 premiers octets de str1 et str2
//     // int result = ft_memcmp(str1, str2, n);
//     int result1 = memcmp(str1, str2, n);

//     if (result1 == 0) {
//         printf("Les deux zones de mémoire sont identiques.\n");
//     } else if (result1 < 0) {
//         printf("%d,
// 	La première zone de mémoire est inférieure à la deuxième.\n", result1);
// //     } else {
// //         printf("%d,
// 	La première zone de mémoire est supérieure à la deuxième.\n", result1);
// //     }

// //     return (0);
// // }