/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maba <maba@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 12:28:56 by maba              #+#    #+#             */
/*   Updated: 2024/03/13 12:41:02 by maba             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_words(char const *s, char c)
{
	int	count;
	int	in_word;

	count = 0;
	in_word = 0;
	while (*s)
	{
		if (*s != c)
		{
			if (!in_word)
				count++;
			in_word = 1;
		}
		else
			in_word = 0;
		s++;
	}
	return (count);
}

static char	*ft_strndup(const char *s, size_t n)
{
	char	*dup;

	dup = (char *)malloc(sizeof(char) * (n + 1));
	if (!dup)
		return (NULL);
	ft_memcpy(dup, s, n);
	dup[n] = '\0';
	return (dup);
}

static char	**ft_free_result(char **result, int i)
{
	while (--i >= 0)
		free(result[i]);
	free(result);
	return (NULL);
}

static char	**ft_fill_word(char **result, const char *start, const char *end,
		int i)
{
	result[i] = ft_strndup(start, end - start);
	if (!result[i])
	{
		return (ft_free_result(result, i));
	}
	return (&result[i]);
}

char	**ft_split(char const *s, char c)
{
	char		**result;
	int			i;
	const char	*start = s;

	if (!s)
		return (NULL);
	result = (char **)malloc(sizeof(char *) * ((ft_count_words(s, c)) + 1));
	if (!result)
		return (NULL);
	i = 0;
	while (*s)
	{
		if (*s != c)
		{
			start = s;
			while (*s && *s != c)
				s++;
			if (!ft_fill_word(result, start, s, i++))
				return (NULL);
		}
		else
			s++;
	}
	result[i] = NULL;
	return (result);
}

// int	main(void)
// {
// 	char const *s = "Hello World, Welcome to Split Function!";
// 	char c = ' ';

// 	printf("Chaine originale: \"%s\"\n", s);
// 	printf("Caractère de séparation: '%c'\n", c);

// 	char **result = ft_split(s, c);

// 	if (result)
// 	{
// 		printf("Mots obtenus après split:\n");
// 		for (int i = 0; result[i] != NULL; i++)
// 		{
// 			printf("[%d] %s\n", i, result[i]);
// 			free(result[i]); // Libérer la mémoire allouée pour chaque mot
// 		}
// 		free(result); // Libérer la mémoire allouée pour le tableau de pointeurs
// 	}
// 	else
// 	{
// 		printf("L'allocation de mémoire a échoué.\n");
// 	}

// 	return (0);
// }