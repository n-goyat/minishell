/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maba <maba@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 12:28:34 by maba              #+#    #+#             */
/*   Updated: 2024/03/11 20:19:07 by maba             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	ft_putstr_fd(s, fd);
	ft_putchar_fd('\n', fd);
}

// int main(void)
// {
//     char *str = "cherif est a l'ecole 42";
//     int fd;

//     fd = 1;
//     ft_putendl_fd(str, fd);
//     return (0);
// }
