/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maba <maba@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 11:54:14 by maba              #+#    #+#             */
/*   Updated: 2024/03/11 19:53:01 by maba             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isprint(int c)
{
	if (c > 31 && c < 127)
		return (1);
	return (0);
}

// int main() {
//     char c = 'A';

//     if (my_isprint(c)) {
//         printf("%c is printable.\n", c);
//     } else {
//         printf("%c is not printable.\n", c);
//     }

//     return (0);
// }