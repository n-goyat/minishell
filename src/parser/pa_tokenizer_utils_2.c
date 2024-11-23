/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pa_tokenizer_utils_2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoyat <ngoyat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 23:57:46 by ngoyat            #+#    #+#             */
/*   Updated: 2024/11/23 04:58:46 by ngoyat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pa_header.h"

void	expand_token_value(t_token *token, t_env_list *env_list)
{
	char	*expanded_value;
	int		i;

	i = 0;
	if (token->type == TOKEN_WORD && token->value[0] == '$')
	{
		expanded_value = expand_single_variable(token->value, &i, env_list);
		free(token->value);
		token->value = expanded_value;
	}
}

int	carve_token(t_token *token, char *typ, int token_len)
{
	token->typ = ft_strdup(typ);
	return (token_len);
}
