/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maba <maba@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 22:11:22 by maba              #+#    #+#             */
/*   Updated: 2024/03/12 12:34:27 by maba             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strcpy(char *dest, const char *src)
{
	int	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strdup(const char *s1)
{
	char	*dup_src;

	dup_src = malloc((ft_strlen(s1) + 1) * sizeof(char));
	if (dup_src == NULL)
		return (NULL);
	dup_src = ft_strcpy(dup_src, s1);
	return (dup_src);
}

// int main(void)
// {
//     const char src[] = "Cherif est actuellement a 42 Heilbronn.";

//     printf("%s\n", ft_strdup(src));
//     return (0);
// }
