/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoyat <ngoyat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 16:59:02 by ngoyat            #+#    #+#             */
/*   Updated: 2024/03/12 17:16:44 by ngoyat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *str, int c, size_t n)
{
	unsigned char	*string;
	unsigned char	uc;
	size_t			i;

	i = 0;
	string = (unsigned char *)str;
	uc = (unsigned char)c;
	while (i < n)
	{
		if (*string == uc)
			return ((void *)str);
		i++;
		string++;
	}
	return (NULL);
}
