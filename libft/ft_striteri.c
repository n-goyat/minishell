/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maba <maba@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 12:29:07 by maba              #+#    #+#             */
/*   Updated: 2024/03/11 20:55:58 by maba             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	unsigned int	count;

	count = 0;
	if (!s || !f)
		return ;
	while (s[count] != '\0')
	{
		f(count, &s[count]);
		count++;
	}
}

// void uppercase(unsigned int index, char *c)
// {
//     if (*c >= 'a' && *c <= 'z')
//         *c -= 32;
// }
// int main()
// {
//     char str[] = "hello world";
//     printf("Chaîne originale: %s\n", str);
//
//     ft_striteri(str, &uppercase);
//     printf("Chaîne transformée: %s\n", str);
//     return (0);
// }
