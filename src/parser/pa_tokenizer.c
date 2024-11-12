/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pa_tokenizer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoyat <ngoyat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 15:10:04 by ngoyat            #+#    #+#             */
/*   Updated: 2024/10/22 13:40:32 by ngoyat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pa_header.h"

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
void	free_token_list(t_token_list *token_list)
{
	t_token	*current;
	t_token	*next;

	current = token_list->head;
	while (current)
	{
		next = current->next;
		free(current->value);
		free(current);
		current = next;
	}
	free(token_list);
}
// Function to add a token to the list
void	add_token(t_token_list *token_list, t_token *new_token)
{
	if (!new_token)
		return ;
	if (!token_list->head)
	{
		token_list->head = new_token;
		token_list->tail = new_token;
	}
	else
	{
		token_list->tail->next = new_token;
		token_list->tail = new_token;
	}
	token_list->size++;
}

t_token_list	*init_token_list(void)
{
	t_token_list	*token_list;

	token_list = malloc(sizeof(t_token_list));
	if (!token_list)
		return (NULL);
	token_list->head = NULL;
	token_list->tail = NULL;
	token_list->size = 0;
	return (token_list);
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
void	print_tokens(t_token_list *token_list)
{
	t_token	*current_token;

	if (!token_list || !token_list->head)
	{
		printf("Token list is empty.\n");
		return ;
	}
	current_token = token_list->head;
	while (current_token != NULL)
	{
		printf("Token: %s, Type: %d\n", current_token->value,
			current_token->type);
		current_token = current_token->next;
	}
}

//&& !strchr("<>|\"\'", word[i])
int	ft_word_len(char *word)
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

int	assign_token_typ(char *in, int *i, t_token *token, t_env_list *env_list)
{
	int	result;

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

// Function to check if a space is needed between two tokens
int	needs_space(t_token *current, t_token *next, const char *input, int i)
{
	if (!next)
		return (0);
	// Check if there is a space in the input string between current and next token positions
	if (input[i] == ' ')
		return (1);
	// No space needed between quotes and words within the same token
	if ((current->type == TOKEN_SIN_QOTES || current->type == TOKEN_DBL_QOTES)
		&& (next->type == TOKEN_WORD || next->type == TOKEN_DBL_QOTES
			|| next->type == TOKEN_SIN_QOTES))
		return (0);
	// Add space between all other types
	return (1);
}

// Function to finalize the token list after tokenizing
void	finalize_token_list(t_token_list *token_list, const char *input,
		int index)
{
	t_token	*current;
	t_token	*next_token;
	char	*new_value;

	current = token_list->head;
	while (current && current->next)
	{
		next_token = current->next;
		// Adjust index to reflect current position in the input string
		index += strlen(current->value);
		// Skip over spaces in the input string to get the correct index position
		while (input[index] == ' ')
			index++;
		if (!needs_space(current, next_token, input, index))
		{
			new_value = ft_strjoin(current->value, next_token->value);
			if (new_value)
			{
				free(current->value);
				current->value = new_value;
				current->next = next_token->next;
				free(next_token->value);
				free(next_token);
				continue ;
			}
		}
		current = current->next;
	}
}

t_token_list	*tokenize_input(char *in, t_env_list *env_list)
{
	t_token_list	*token_list;
	t_token			*new_token;
	int				i;

	i = 0;
	token_list = init_token_list();
	if (!token_list)
		return (NULL);
	while (in[i])
	{
		if (in[i] == ' ')
		{
			i++;
			continue ;
		}
		new_token = create_token(NULL, 0);
		if (assign_token_typ(in, &i, new_token, env_list) == -1)
		{
			free_token_list(token_list);
			return (NULL);
		}
		add_token(token_list, new_token);
	}
	finalize_token_list(token_list, in, i); // Pass the input string
	return (token_list);
}