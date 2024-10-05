/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maba <maba@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 11:55:13 by maba              #+#    #+#             */
/*   Updated: 2024/03/14 10:58:34 by maba             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	len_dest;
	size_t	len_src;
	size_t	count;

	count = 0;
	len_dest = 0;
	len_src = 0;
	while (dest[len_dest] != '\0' && len_dest < size)
		len_dest++;
	while (src[len_src] != '\0')
		len_src++;
	if (size == 0)
		return (len_src);
	if (size <= len_dest)
		return (len_src + size);
	while (src[count] != '\0' && len_dest + count < (size - 1))
	{
		dest[len_dest + count] = src[count];
		count++;
	}
	if (len_dest + count < size)
		dest[len_dest + count] = '\0';
	return (len_dest + len_src);
}
