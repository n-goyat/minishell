/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maba <maba@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 11:51:45 by maba              #+#    #+#             */
/*   Updated: 2024/03/11 19:51:03 by maba             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else if (c >= 'a' && c <= 'z')
		return (1);
	else if (c >= 'A' && c <= 'Z')
		return (1);
	return (0);
}

// int main() {
//     char test_char = '7'; // Caractère à tester

//
//     if (ft_isalnum(test_char)) {
//         printf("Le caractère %c est alphanumérique.\n", test_char);
//     } else {
//         printf("Le caractère %c n'est pas alphanumérique.\n", test_char);
//     }

//     return 0;
// }