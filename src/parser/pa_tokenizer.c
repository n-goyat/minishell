/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pa_tokenizer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoyat <ngoyat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 15:10:04 by ngoyat            #+#    #+#             */
/*   Updated: 2024/11/23 04:58:39 by ngoyat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pa_header.h"

int	write_token(char *in, int *i, t_token *token, t_token_type typ)
{
	int	token_length;

	token->type = typ;
	if (typ == TOKEN_REDIRECT_IN || typ == TOKEN_REDIRECT_OUT)
		token_length = carve_token(token, ">", 1);
	else if (typ == TOKEN_APPEND || typ == TOKEN_HEREDOC)
		token_length = carve_token(token, ">>", 2);
	else if (typ == TOKEN_PIPE)
		token_length = carve_token(token, "|", 1);
	else if (typ == TOKEN_DBL_QOTES || typ == TOKEN_SIN_QOTES)
	{
		token_length = handle_quotes(in + *i, token, typ);
		if (token_length == -1)
		{
			return (-1);
		}
	}
	else
	{
		token_length = ft_word_len(in + *i);
		token->value = ft_strndup(in + *i, token_length);
	}
	*i += token_length;
	return (0);
}

int	handle_quotes(char *in, t_token *token, t_token_type typ)
{
	int		i;
	char	quote_char;

	if (typ == TOKEN_DBL_QOTES)
		quote_char = '\"';
	else if (typ == TOKEN_SIN_QOTES)
		quote_char = '\'';
	else
		return (-1);
	i = 1;
	while (in[i] != quote_char && in[i] != '\0')
		i++;
	if (in[i] != quote_char)
		return (-1);
	token->value = ft_strndup(in + 1, i - 1);
	return (i + 1);
}

int	assign_token_typ(char *in, int *i, t_token *token, t_env_list *env_list)
{
	int	result;

	token->position = *i;
	if (strncmp(in + *i, "<<", 2) == 0)
		result = (write_token(in, i, token, TOKEN_HEREDOC));
	else if (strncmp(in + *i, ">>", 2) == 0)
		result = (write_token(in, i, token, TOKEN_APPEND));
	else if (strncmp(in + *i, "<", 1) == 0)
		result = (write_token(in, i, token, TOKEN_REDIRECT_IN));
	else if (strncmp(in + *i, ">", 1) == 0)
		result = (write_token(in, i, token, TOKEN_REDIRECT_OUT));
	else if (strncmp(in + *i, "|", 1) == 0)
		result = (write_token(in, i, token, TOKEN_PIPE));
	else if (strncmp(in + *i, "\"", 1) == 0)
		result = (write_token(in, i, token, TOKEN_DBL_QOTES));
	else if (strncmp(in + *i, "\'", 1) == 0)
		result = (write_token(in, i, token, TOKEN_SIN_QOTES));
	else
		result = (write_token(in, i, token, TOKEN_WORD));
	expand_token_value(token, env_list);
	return (result);
}

// Helper function to create and process a token
int	process_token(char *in, int *i, t_token_list *token_list,
		t_env_list *env_list)
{
	t_token	*new_token;

	new_token = create_token();
	if (!new_token)
		return (-1);
	new_token->position = *i;
	if (assign_token_typ(in, i, new_token, env_list) == -1)
	{
		free(new_token);
		return (-1);
	}
	add_token(token_list, new_token);
	return (0);
}

// Main function to tokenize input
t_token_list	*tokenize_input(char *in, t_env_list *env_list)
{
	t_token_list	*token_list;
	int				i;

	i = 0;
	token_list = init_token_list();
	if (!token_list)
		return (NULL);
	while (in && in[i])
	{
		skip_whitespace(in, &i);
		if (!in[i])
			break ;
		if (process_token(in, &i, token_list, env_list) == -1)
		{
			free_token_list(token_list);
			return (NULL);
		}
	}
	finalize_token_list(token_list, in);
	return (token_list);
}
