/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pa_tokenizer_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoyat <ngoyat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 23:57:39 by ngoyat            #+#    #+#             */
/*   Updated: 2024/11/18 23:57:42 by ngoyat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pa_header.h"

int	ft_word_len(char *word)
{
	int	i;

	i = 0;
	while (word[i] != ' ' && word[i] != '\0')
		i++;
	return (i);
}

// Function to check if a space is needed between two tokens
int	needs_space(t_token *current, t_token *next, const char *input)
{
	int	pos_after_current;

	if (!next || !current || !(current->value))
		return (0);
	pos_after_current = current->position + ft_strlen(current->value);
	while (pos_after_current < next->position)
	{
		if (input[pos_after_current] == ' ')
			return (1);
		pos_after_current++;
	}
	if ((current->type == TOKEN_SIN_QOTES || current->type == TOKEN_DBL_QOTES)
		&& (next->type == TOKEN_WORD || next->type == TOKEN_DBL_QOTES
			|| next->type == TOKEN_SIN_QOTES))
		return (0);
	if (current->type == TOKEN_WORD && (next->type == TOKEN_WORD
			|| next->type == TOKEN_OTHER))
		return (0);
	return (1);
}

void	finalize_token_list(t_token_list *token_list, const char *input)
{
	t_token	*current;
	t_token	*next_token;
	char	*new_value;

	current = token_list->head;
	while (current && current->next)
	{
		next_token = current->next;
		if (needs_space(current, next_token, input) == 0)
		{
			if (current->value == NULL)
			{
				current = current->next;
				continue ;
			}
			new_value = ft_strjoin(current->value, next_token->value);
			if (new_value)
			{
				concatenate_tokens(current, current->next, new_value);
				continue ;
			}
		}
		current = current->next;
	}
}

void	concatenate_tokens(t_token *current, t_token *next_token,
		char *new_value)
{
	free(current->value);
	current->value = new_value;
	current->next = next_token->next;
	free(next_token->value);
	free(next_token);
}

// Helper function to skip whitespace
void	skip_whitespace(char *in, int *i)
{
	while (in[*i] == ' ')
		(*i)++;
}
