/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maba <maba@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 11:55:06 by maba              #+#    #+#             */
/*   Updated: 2024/03/13 12:18:14 by maba             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int	count;

	count = 0;
	while (s[count] != '\0')
	{
		if (s[count] == (char)c)
			return ((char *)s + count);
		count++;
	}
	if ((char)c == '\0')
		return ((char *)s + count);
	return (NULL);
}

// int	main(void)
// {
// 	const char	*str = "Hello, World!";
// 	char		*ptr;

// 	ptr = ft_strchr(str, 'W');
// 	if (ptr != NULL)
// 	{
// 		printf("Caractère 'W' trouvé à la position : %ld\n", ptr - str);
// 	}
// 	else
// 	{
// 		printf("Caractère 'W' non trouvé dans la chaîne.\n");
// 	}
// 	return (0);
// }
