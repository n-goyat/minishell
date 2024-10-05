/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maba <maba@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 22:54:37 by maba              #+#    #+#             */
/*   Updated: 2024/03/11 15:03:26 by maba             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_in_set(char c, const char *set)
{
	int	count;

	count = 0;
	while (set[count] != '\0')
	{
		if (set[count] == c)
			return (1);
		count++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	char	*trimmed;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	while (s1[start] && is_in_set(s1[start], set))
		start++;
	if (s1[start] == '\0')
		return (ft_strdup(""));
	end = ft_strlen(s1) - 1;
	while (end > start && is_in_set(s1[end], set))
		end--;
	trimmed = (char *)malloc(sizeof(char) * (end - start + 2));
	if (!trimmed)
		return (NULL);
	ft_strlcpy(trimmed, s1 + start, end - start + 2);
	return (trimmed);
}

// int	main(void)
// {
// 	const char	*s1 = "   hello world   ";
// 	const char	*set = " ";
// 	char		*trimmed;

// 	printf("Chaîne originale: \"%s\"\n", s1);
// 	printf("Set de caractères à trimmer: \"%s\"\n", set);
// 	trimmed = ft_strtrim(s1, set);
// 	if (trimmed)
// 	{
// 		printf("Chaîne trimmée: \"%s\"\n", trimmed);
// 		free(trimmed);
// 	}
// 	else
// 	{
// 		printf("L'allocation de mémoire a échoué.\n");
// 	}
// 	return (0);
// }
