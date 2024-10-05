/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maba <maba@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 11:52:00 by maba              #+#    #+#             */
/*   Updated: 2024/03/08 21:57:24 by maba             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
		return (1);
	return (0);
}

// int	main(void)
// {
// 	char test_char = 'a';

// 	if (ft_isalpha(test_char))
// 		printf("%c est une lettre alphabétique.\n", test_char);
// 	else
// 		printf("%c n'est pas une lettre alphabétique.\n", test_char);

// 	return (0);
// }
