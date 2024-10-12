/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoyat <ngoyat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 14:55:45 by ngoyat            #+#    #+#             */
/*   Updated: 2024/03/18 15:26:08 by ngoyat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	count_words(const char *s, char c)
{
	size_t	words;
	size_t	i;

	i = 0;
	words = 0;
	while (s[i])
	{
		if (*(s + i) != c)
		{
			words++;
			while (*(s + i) && *(s + i) != c)
				i++;
		}
		else if (*(s + i) == c)
			i++;
	}
	return (words);
}

size_t	word_len(char const *s, char c, size_t i)
{
	size_t	len;

	len = 0;
	while (s[i] && s[i] != c)
	{
		len++;
		i++;
	}
	return (len);
}

void	ft_free(char **arr, size_t index)
{
	if (index == 0)
	{
		free(arr);
		return ;
	}
	while (index > 0)
	{
		index--;
		free(arr[index]);
	}
	free(arr);
}

char	**splitter(char const *s, char c, char **arr)
{
	size_t	i;
	size_t	j;
	size_t	words;

	i = 0;
	j = 0;
	words = count_words(s, c);
	while (j < words)
	{
		while (*(s + i) && *(s + i) == c)
			i++;
		*(arr + j) = ft_substr(s, i, word_len(s, c, i));
		if (!*(arr + j))
		{
			ft_free(arr, j);
			return (NULL);
		}
		while (*(s + i) && *(s + i) != c)
			i++;
		j++;
	}
	*(arr + j) = (char *) NULL;
	return (arr);
}

char	**ft_split(char const *s, char c)
{
	char	**arr;
	size_t	words;

	if (!s)
		return (NULL);
	words = count_words(s, c);
	arr = (char **)malloc(sizeof(char *) * (words + 1));
	if (!arr)
		return (NULL);
	return (splitter(s, c, arr));
}
