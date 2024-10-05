/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maba <maba@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 14:09:19 by maba              #+#    #+#             */
/*   Updated: 2024/03/30 00:57:07 by maba             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t	total_size;
	void	*ptr;

	total_size = count * size;
	ptr = malloc(total_size);
	if (ptr == NULL)
	{
		return (NULL);
	}
	ft_memset(ptr, 0, total_size);
	return (ptr);
}

// int main(void) {
//     // Définir le nombre d'éléments et la taille de chaque élément
//     size_t count = 5;
//     size_t size = sizeof(int);

//     // Appeler ft_calloc pour allouer de la mémoire et l'initialiser à zéro
//     ft_calloc(count, size);

//     // Vérifier si la mémoire a été correctement allouée et initialisée
//

//     printf("Mémoire allouée et initialisée avec succès !\n");

//     return (0);
// }