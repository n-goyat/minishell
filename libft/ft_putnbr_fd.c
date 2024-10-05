/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maba <maba@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 12:28:42 by maba              #+#    #+#             */
/*   Updated: 2024/03/11 20:26:27 by maba             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	gestion_error(int nb, int fd)
{
	if (nb < INT_MIN || nb > INT_MAX)
		return ;
	if (nb == 0)
	{
		ft_putchar_fd('0', fd);
		return ;
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	long int	number;
	int			count;
	long int	i;

	gestion_error(n, fd);
	number = n;
	i = 1;
	if (number < 0)
	{
		ft_putchar_fd('-', fd);
		number = -1 * number;
	}
	count = 0;
	while (number / i > 0)
	{
		count++;
		i = i * 10;
	}
	while (count > 0)
	{
		i = i / 10;
		ft_putchar_fd(number / i + '0', fd);
		count--;
		number = number % i;
	}
}

// int main(void)
// {
// 	ft_putnbr_fd(-789, 1);
// 	ft_putchar_fd('\n', 1);
// 	ft_putnbr_fd(0, 1);
// 	ft_putchar_fd('\n', 1);
// 	ft_putnbr_fd(9, 1);
// 	ft_putchar_fd('\n', 1);
// 	ft_putnbr_fd(INT_MAX, 1);
// 	ft_putchar_fd('\n', 1);
// 	ft_putnbr_fd(INT_MIN, 1);

// 	return (0);
// }
