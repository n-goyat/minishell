/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maba <maba@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 14:22:36 by maba              #+#    #+#             */
/*   Updated: 2024/03/12 14:23:26 by maba             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*p;

	p = s;
	while (n-- > 0)
		*p++ = 0;
}

// int	main(void)
// {
// 	char buffer[10];

// 	// Remplir le buffer avec des 'x'
// 	printf("Avant ft_bzero : %s\n", buffer);
// 	ft_bzero(buffer, sizeof(buffer));
// 	buffer[sizeof(buffer) - 1] = '\0';
		// Ajouter un caractère nul à la fin du buffer
// 	printf("Après ft_bzero : %s\n", buffer);
// 	return (0);
// }