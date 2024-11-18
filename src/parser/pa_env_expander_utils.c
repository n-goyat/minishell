/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pa_env_expander_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoyat <ngoyat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 23:58:27 by ngoyat            #+#    #+#             */
/*   Updated: 2024/11/18 23:58:30 by ngoyat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pa_header.h"

// Utility function to concatenate two strings and free the first one
char	*ft_strjoin_free(char *s1, const char *s2)
{
	char	*result;
	size_t	len1;
	size_t	len2;

	if (!s1 || !s2)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	result = malloc(len1 + len2 + 1);
	if (!result)
	{
		free(s1);
		return (NULL);
	}
	ft_memcpy(result, s1, len1);
	ft_memcpy(result + len1, s2, len2 + 1);
	free(s1);
	return (result);
}

char	**split_and_free(char *str, char *delim)
{
	char	**result;

	result = ft_split(str, *delim);
	free(str);
	return (result);
}

char	*append_character(char *result, char c)
{
	char	tmp[2];

	tmp[0] = c;
	tmp[1] = '\0';
	return (ft_strjoin_free(result, tmp));
}

// Helper function to check if the current position is inside single quotes
int	inside_single_quotes(const char *str, int pos)
{
	int	i;
	int	quote_count;

	i = 0;
	quote_count = 0;
	while (i < pos)
	{
		if (str[i] == '\'')
			quote_count++;
		i++;
	}
	return (quote_count % 2 != 0);
}

char	*quotes(t_token **token)
{
	return (ft_strdup((*token)->value));
}
