/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pa_tokenizer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoyat <ngoyat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 15:10:04 by ngoyat            #+#    #+#             */
/*   Updated: 2024/10/17 15:34:37 by ngoyat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pa_header.h"

// Function to create a new token
t_token	*create_token(char *value, int type)
{
	t_token	*new_token;

	(void)value;
	(void)type;
	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->value = NULL;
	new_token->type = 0;
	new_token->next = NULL;
	return (new_token);
}

// Function to add a token to the list
void	add_token(t_token **token_list, t_token *new_token)
{
	t_token	*temp;

	if (!new_token)
		return ;
	temp = *token_list;
	if (!*token_list)
	{
		*token_list = new_token;
		return ;
	}
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = new_token;
}

// Function to determine the token type
int	determine_type(char *token)
{
	if (strcmp(token, "|") == 0)
		return (TOKEN_PIPE);
	if (strcmp(token, "<") == 0)
		return (TOKEN_REDIRECT_IN);
	if (strcmp(token, ">") == 0)
		return (TOKEN_REDIRECT_OUT);
	if (strcmp(token, ">>") == 0)
		return (TOKEN_APPEND);
	if (strcmp(token, "\'") == 0)
		return (TOKEN_SIN_QOTES);
	if (strcmp(token, "\"") == 0)
		return (TOKEN_DBL_QOTES);
	return (TOKEN_WORD);
}

// Function to print tokens (for testing)
void	print_tokens(t_token *tokens)
{
	while (tokens != NULL)
	{
		printf("Token: %s, Type: %d\n", tokens->value, tokens->type);
		tokens = tokens->next;
	}
}

int	word_len(char *word)
{
	int	i;

	i = 0;
	while (word[i] != ' ' && word[i] != '\0')
		i++;
	return (i);
}

int	write_token(char *in, int *i, t_token *token, t_token_type typ)
{
	int	token_length;

	token->type = typ;
	if (typ == TOKEN_REDIRECT_IN || typ == TOKEN_REDIRECT_OUT)
		token_length = 1;
	else if (typ == TOKEN_APPEND || typ == TOKEN_HEREDOC)
		token_length = 2;
	else if (typ == TOKEN_PIPE)
		token_length = 1;
	else if (typ == TOKEN_DBL_QOTES || typ == TOKEN_SIN_QOTES)
	{
		token_length = handle_quotes(in + *i, token, typ);
		if (token_length == -1)
		{
			printf("Syntax error: Unclosed quotes\n");
			return (-1);
		}
	}
	else
		token_length = word_len(in + *i);
	if (typ != TOKEN_DBL_QOTES && typ != TOKEN_SIN_QOTES)
		token->value = ft_strndup(in + *i, token_length);
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
	while (in[i] != quote_char)
	{
		if (in[i] == '\0')
			return (-1);
		i++;
	}
	token->value = ft_strndup(in + 1, i - 1);
	return (i + 1);
}

int	assign_token_typ(char *in, int *i, t_token *token)
{
	if (strncmp(in + *i, "<<", 2) == 0)
		return (write_token(in, i, token, TOKEN_HEREDOC));
	else if (strncmp(in + *i, ">>", 2) == 0)
		return (write_token(in, i, token, TOKEN_APPEND));
	else if (strncmp(in + *i, "<", 1) == 0)
		return (write_token(in, i, token, TOKEN_REDIRECT_IN));
	else if (strncmp(in + *i, ">", 1) == 0)
		return (write_token(in, i, token, TOKEN_REDIRECT_OUT));
	else if (strncmp(in + *i, "|", 1) == 0)
		return (write_token(in, i, token, TOKEN_PIPE));
	else if (strncmp(in + *i, "\"", 1) == 0)
		return (write_token(in, i, token, TOKEN_DBL_QOTES));
	else if (strncmp(in + *i, "\'", 1) == 0)
		return (write_token(in, i, token, TOKEN_SIN_QOTES));
	else
		return (write_token(in, i, token, TOKEN_WORD));
}

t_token	*tokenize_input(char *in)
{
	t_token	*begin;
	t_token	*curry;
	int		i;

	i = 0;
	begin = NULL;
	curry = NULL;
	while (in[i])
	{
		if (in[i] == ' ')
		{
			i++;
			continue ;
		}
		curry = create_token(NULL, 0);
		if (assign_token_typ(in, &i, curry) == -1)
			return (NULL);
		add_token(&begin, curry);
	}
	return (begin);
}
