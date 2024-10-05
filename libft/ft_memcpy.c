/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maba <maba@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 11:54:42 by maba              #+#    #+#             */
/*   Updated: 2024/03/12 15:09:33 by maba             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	const unsigned char	*source;
	unsigned char		*destination;
	size_t				count;

	if (!dst && !src)
		return (NULL);
	source = (const unsigned char *)src;
	destination = (unsigned char *)dst;
	count = 0;
	while (count < n)
	{
		destination[count] = source[count];
		count++;
	}
	return (destination);
}

// int	main(void)
// {
// 	char src[] = "Hello, world!";
// 	char dst[20];
// 	size_t n = 13; // Nombre d'octets à copier

//
// 	ft_memcpy(dst, src, n);

// 	// Affichage des données copiées dans dst
// 	printf("Contenu de dst après ft_memcpy: %s\n", dst);

// 	return (0);
// }