/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoyat <ngoyat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 19:19:36 by ngoyat            #+#    #+#             */
/*   Updated: 2024/03/14 19:11:10 by ngoyat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	int_size(int n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		n = -n;
	while (n > 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char	*test_edge(int n)
{
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	return (NULL);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		sign;
	int		tmp;

	sign = 0;
	if (n == -2147483648)
		return (test_edge(n));
	tmp = int_size(n);
	if (n < 0)
	{
		sign = 1;
		n = -n;
	}
	str = (char *)malloc(tmp + sign + 1);
	if (!str)
		return (NULL);
	str[tmp + sign] = '\0';
	while (tmp--)
	{
		str[tmp + sign] = n % 10 + '0';
		n = n / 10;
	}
	if (sign == 1)
		str[0] = '-';
	return (str);
}
