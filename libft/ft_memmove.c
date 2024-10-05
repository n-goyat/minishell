/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maba <maba@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 11:54:52 by maba              #+#    #+#             */
/*   Updated: 2024/03/08 22:25:53 by maba             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	const unsigned char	*source;
	unsigned char		*destination;
	size_t				count;

	source = (const unsigned char *)src;
	destination = (unsigned char *)dst;
	count = 0;
	if (destination < source)
	{
		while (count < len)
		{
			destination[count] = source[count];
			count++;
		}
	}
	else if (destination > source)
	{
		while (len > 0)
		{
			destination[len - 1] = source[len - 1];
			len = len - 1;
		}
	}
	return (destination);
}

// int	main(void)
// {
// 	char	src[] = "Hello, world!";
// 	char	dst[20];

// 	size_t len = 13; // Nombre d'octets à copier
// 	// Copie avec ft_memmove
// 	ft_memmove(dst, src, len);
// 	// Affichage des données copiées dans dst
// 	printf("Contenu de dst après ft_memmove: %s\n", dst);
// 	return (0);
// }
