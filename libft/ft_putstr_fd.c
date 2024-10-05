/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maba <maba@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 12:28:49 by maba              #+#    #+#             */
/*   Updated: 2024/03/11 20:27:07 by maba             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	int	count;

	count = 0;
	while (s[count] != '\0')
	{
		ft_putchar_fd(s[count], fd);
		count++;
	}
}

// int main(void)
// {
//     char *str = "cherif est a l'ecole 42";
//     int fd;

//     fd = 1;
//     ft_putstr_fd(str, fd);
//     return (0);
// }
