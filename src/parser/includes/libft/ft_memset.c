/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoyat <ngoyat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 18:50:25 by ngoyat            #+#    #+#             */
/*   Updated: 2024/03/11 22:27:40 by ngoyat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *dest, int c, size_t n)
{
	unsigned char	*dst;
	unsigned char	uc;

	uc = c;
	dst = (unsigned char *)dest;
	while (n > 0)
	{
		*(dst++) = uc;
		n--;
	}
	return (dest);
}
