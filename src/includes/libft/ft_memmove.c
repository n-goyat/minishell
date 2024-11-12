/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoyat <ngoyat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 00:07:43 by ngoyat            #+#    #+#             */
/*   Updated: 2024/03/12 17:11:29 by ngoyat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char		*tmp_dst;
	const char	*tmp_src;
	size_t		i;

	i = 0;
	tmp_dst = (char *)dst;
	tmp_src = (const char *)src;
	if (tmp_dst > tmp_src)
	{
		while (len--)
			tmp_dst[len] = tmp_src[len];
	}
	else if (tmp_dst < tmp_src)
	{
		while (i < len)
		{
			tmp_dst[i] = tmp_src[i];
			i++;
		}
	}
	return (dst);
}
