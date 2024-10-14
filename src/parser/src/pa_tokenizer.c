/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pa_tokenizer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoyat <ngoyat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 15:10:04 by ngoyat            #+#    #+#             */
/*   Updated: 2024/10/14 18:08:32 by ngoyat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pa_header.h"

// Function to create a new token
t_token	*create_token(char *value, int type)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->value = strdup(value);
	new_token->type = type;
	new_token->next = NULL;
	return (new_token);
}

// Function to add a token to the list
void	add_token(t_token **token_list, t_token *new_token)
{
	t_token	*temp;

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
	return (TOKEN_ARGUMENT);
}

// Function to handle quotes and update buffer
int	handle_quotes(t_tokenizer_state *state)
{
	char	quote_char;

	quote_char = state->input[state->i];
	state->i++; // Skip the opening quote
	while (state->input[state->i] != '\0'
		&& state->input[state->i] != quote_char)
	{
		state->buffer[state->buf_index++] = state->input[state->i];
		state->i++;
	}
	state->i++; // Skip the closing quote
	return (state->buf_index);
}

// Helper function to handle the '>>' operator
void	handle_double_greater(t_tokenizer_state *state)
{
	add_token(state->token_list, create_token(">>", TOKEN_APPEND));
	state->i += 2; // Skip '>>'
}

// Function to handle operators like |, <, >
int	handle_operator(t_tokenizer_state *state)
{
	char	operator_str[2] = {state->input[state->i], '\0'};

	if (state->buf_index > 0)
	{
		state->buffer[state->buf_index] = '\0';
		add_token(state->token_list, create_token(state->buffer,
				determine_type(state->buffer)));
		state->buf_index = 0;
	}
	if (state->input[state->i] == '>' && state->input[state->i + 1] == '>')
	{
		handle_double_greater(state);
	}
	else
	{
		add_token(state->token_list, create_token(operator_str,
				determine_type(operator_str)));
		state->i++;
	}
	return (state->buf_index);
}

// Function to add the buffer content as a token
int	add_buffer_to_tokens(t_tokenizer_state *state)
{
	if (state->buf_index > 0)
	{
		state->buffer[state->buf_index] = '\0';
		add_token(state->token_list, create_token(state->buffer,
				determine_type(state->buffer)));
		state->buf_index = 0;
	}
	return (state->buf_index);
}

// Function to process each character of input
int	process_input_char(t_tokenizer_state *state)
{
	if (state->input[state->i] == '"' || state->input[state->i] == '\'')
	{
		state->buf_index = handle_quotes(state);
	}
	else if (isspace(state->input[state->i]))
	{
		state->buf_index = add_buffer_to_tokens(state);
		state->i++;
	}
	else if (state->input[state->i] == '|' || state->input[state->i] == '<'
		|| state->input[state->i] == '>')
	{
		state->buf_index = handle_operator(state);
	}
	else
	{
		state->buffer[state->buf_index++] = state->input[state->i];
		state->i++;
	}
	return (state->buf_index);
}

// Main tokenizer function
t_token	*tokenize_input(char *input)
{
	t_token				*token_list;
	t_tokenizer_state	state;

	token_list = NULL;
	state.input = input;
	state.buffer[0] = '\0';
	state.buf_index = 0;
	state.i = 0;
	state.token_list = &token_list;
	while (state.input[state.i] != '\0')
	{
		state.buf_index = process_input_char(&state);
	}
	// Add any remaining buffer content as a final token
	state.buf_index = add_buffer_to_tokens(&state);
	return (token_list);
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

// Test the tokenizer
// int	main(void)
// {
// 	char	input[] = "echo 'hello world' | grep world >> output.txt";
// 	t_token	*tokens;

// 	tokens = tokenize_input(input);
// 	print_tokens(tokens);
// 	// Free tokens...
// 	return (0);
// }
