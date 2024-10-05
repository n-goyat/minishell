/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maba <maba@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 12:27:21 by maba              #+#    #+#             */
/*   Updated: 2024/03/12 13:53:18 by maba             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_digits(int n)
{
	int	count;

	count = 1;
	while (n / 10 != 0)
	{
		count++;
		n = n / 10;
	}
	return (count);
}

static int	ft_sign(int n)
{
	if (n < 0)
		return (-1);
	return (1);
}

char	*ft_itoa(int n)
{
	int		sign;
	int		digits;
	char	*str;

	sign = ft_sign(n);
	digits = count_digits(n);
	if (sign == -1)
		digits++;
	str = (char *)malloc(sizeof(char) * (digits + 1));
	if (str == NULL)
		return (NULL);
	str[digits] = '\0';
	while (digits-- > 0)
	{
		str[digits] = (n % 10) * sign + '0';
		n /= 10;
	}
	if (sign == -1)
		str[0] = '-';
	return (str);
}

// int main(void) {
//     int num = -12345; // Un exemple de nombre entier

//
//     char *str = ft_itoa(num);

//     if (str) {
//         printf("Entier: %d\n", num);
//         printf("Chaîne de caractères: %s\n", str);
//         free(str); // Libération de la mémoire allouée dynamiquement
//     } else {
//         printf("L'allocation de mémoire a échoué.\n");
//     }

//     return (0);
// }
