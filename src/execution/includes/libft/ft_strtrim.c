/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoyat <ngoyat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 22:59:43 by ngoyat            #+#    #+#             */
/*   Updated: 2024/03/18 15:28:25 by ngoyat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	is_set_character(char c, char const *set)
{
	while (*set)
	{
		if (*set == c)
		{
			return (1);
		}
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	len;
	size_t	start;
	size_t	end;
	char	*tmp;

	if (!s1 || !set)
		return (NULL);
	len = ft_strlen(s1);
	start = 0;
	while (start < len && is_set_character(s1[start], set))
		start++;
	end = len;
	while (end > start && is_set_character(s1[end - 1], set))
		end--;
	len = end - start;
	tmp = (char *)malloc((len) + 1);
	if (!tmp)
		return (NULL);
	ft_memcpy(tmp, s1 + start, len);
	tmp[len] = 0;
	return (tmp);
}
