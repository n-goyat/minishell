/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoyat <ngoyat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 21:12:54 by ngoyat            #+#    #+#             */
/*   Updated: 2024/03/11 23:20:30 by ngoyat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char		*tmp_dst;
	const char	*tmp_src;

	if ((dst == src) || n == 0)
		return (dst);
	if (!dst && !src)
		return (0);
	tmp_dst = (char *)dst;
	tmp_src = (const char *)src;
	while (n--)
	{
		tmp_dst[n] = tmp_src[n];
	}
	return (dst);
}
