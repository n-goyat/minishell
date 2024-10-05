/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maba <maba@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 12:29:26 by maba              #+#    #+#             */
/*   Updated: 2024/03/11 21:15:07 by maba             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*result;
	size_t	len;
	size_t	count;

	count = 0;
	len = ft_strlen(s);
	result = (char *)malloc(sizeof(char) * (len + 1));
	if (result == NULL)
		return (NULL);
	while (count < len)
	{
		result[count] = f(count, s[count]);
		count++;
	}
	result[len] = '\0';
	return (result);
}

// char uppercase(unsigned int index, char c)
// {
//     // Si le caractère est minuscule, le convertir en majuscule
//     if (c >= 'a' && c <= 'z')
//         return (c - 32); // Conversion en majuscule
//     return (c); // Sinon, retourner le caractère tel quel
// }
// int main()
// {
//     const char *str = "Hello World";
//
//     char *result = ft_strmapi(str, &uppercase);
//     if (result)
//     {
//         printf("Chaîne originale: %s\n", str);
//         printf("Chaîne transformée: %s\n", result);
//         // Libérer la mémoire allouée pour le résultat
//         free(result);
//     }
//     else
//     {
//         printf("Allocation de mémoire échouée.\n");
//     }
//     return (0);
// }
