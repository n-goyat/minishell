/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoyat <ngoyat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 22:23:02 by ngoyat            #+#    #+#             */
/*   Updated: 2024/03/12 22:59:09 by ngoyat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*tmp;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	tmp = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!tmp)
		return (NULL);
	while (s1[j])
	{
		tmp[i] = s1[j];
		i++;
		j++;
	}
	j = 0;
	while (s2[j])
	{
		tmp[i] = s2[j];
		i++;
		j++;
	}
	tmp[i] = 0;
	return (tmp);
}
