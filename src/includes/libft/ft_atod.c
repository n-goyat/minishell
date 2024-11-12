/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoyat <ngoyat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 13:27:43 by ngoyat            #+#    #+#             */
/*   Updated: 2024/07/02 13:34:12 by ngoyat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static double	post_dot_cal(char *str, int i)
{
	double	res;
	double	pow;

	pow = 1;
	res = 0;
	while (str && str[i])
	{
		pow /= 10;
		res = res + (str[i++] - 48) * pow;
	}
	return (res);
}

double	atod(char *str)
{
	int		sign;
	long	pre_dot;
	double	post_dot;
	int		i;

	pre_dot = 0;
	post_dot = 0;
	sign = 1;
	i = 0;
	while (str && ((str[i] >= 9 && str[i] <= 13) || str[i] == 32))
		i++;
	while (str && (str[i] == '+' || str[i] == '-'))
	{
		if (str[i] == '-')
			sign = -sign;
		i++;
	}
	while (str && str[i] && str[i] != '.')
		pre_dot = (pre_dot * 10) + (str[i++] - 48);
	if ('.' == str[i++])
		post_dot = post_dot_cal(str, i);
	return ((pre_dot + post_dot) * sign);
}
