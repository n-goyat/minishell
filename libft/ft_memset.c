/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maba <maba@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 11:54:59 by maba              #+#    #+#             */
/*   Updated: 2024/03/11 17:55:13 by maba             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*buffer;
	unsigned char	c_value;
	size_t			count;

	buffer = (unsigned char *)b;
	c_value = (unsigned char)c;
	count = 0;
	while (count < len)
	{
		buffer[count] = c_value;
		count++;
	}
	return (buffer);
}

// int	main(void)
// {
// 	char buffer[20]; // Zone mémoire à initialiser
// 	int value = '@'; // Valeur à copier dans la zone mémoire
// 	size_t len = 10; // Nombre d'octets à initialiser

// 	// Appel de la fonction ft_memset pour initialiser la zone mémoire
// 	ft_memset(buffer, value, len);

// 	// Affichage du contenu de la zone mémoire après initialisation
// 	printf("Contenu de buffer après ft_memset: %s\n", buffer);

// 	return (0);
// }