/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maba <maba@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 12:28:28 by maba              #+#    #+#             */
/*   Updated: 2024/03/11 20:18:25 by maba             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

// int	main(void)
// {
// 	int fd = 1;
// 	ft_putchar_fd('H', fd);
// 	ft_putchar_fd('e', fd);
// 	ft_putchar_fd('l', fd);
// 	ft_putchar_fd('l', fd);
// 	ft_putchar_fd('o', fd);
// 	// Écriture d'un saut de ligne
// 	ft_putchar_fd('\n', fd);
// 	return (0);
// }
