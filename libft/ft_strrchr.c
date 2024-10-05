/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maba <maba@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 11:56:00 by maba              #+#    #+#             */
/*   Updated: 2024/03/13 15:06:37 by maba             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	while (i >= 0)
	{
		if (s[i] == (char)c)
		{
			return ((char *)(s + i));
		}
		i--;
	}
	return (NULL);
}

// int	main(void)
// {
// 	const char	*str = "hello world";
// 	char		*ptr;

// 	ptr = ft_strrchr(str, 'l');
// 	if (ptr != NULL)
// 	{
// 		printf("Dernière occurrence de 'l' : %s\n", ptr);
// 	}
// 	else
// 	{
// 		printf("Le caractère n'est pas trouvé.\n");
// 	}
// 	return (0);
// }