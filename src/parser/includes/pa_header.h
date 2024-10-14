/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pa_header.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoyat <ngoyat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 17:41:05 by ngoyat            #+#    #+#             */
/*   Updated: 2024/10/14 18:09:16 by ngoyat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PA_HEADER_H
# define PA_HEADER_H

# include "./libft/libft.h"
# include <ctype.h>
# include <limits.h>
# include <stdarg.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct s_token
{
	char			*value;
	int				type;
	struct s_token	*next;
}					t_token;

typedef enum e_token_type
{
	TOKEN_COMMAND,
	TOKEN_ARGUMENT,
	TOKEN_PIPE,
	TOKEN_REDIRECT_IN,
	TOKEN_REDIRECT_OUT,
	TOKEN_APPEND,
	TOKEN_OTHER
}					t_token_type;

// Struct to hold the tokenization state
typedef struct s_tokenizer_state
{
	char			*input;
	char			buffer[1024];
	int				buf_index;
	int				i;
	t_token			**token_list;
}					t_tokenizer_state;

//	pa_main_env_creation
t_env				*create_node(char *env_var);
void				add_node(t_env **env_list, t_env *new_node);
t_env				*init_env_list(char **env);
void				print_env_list(t_env *env_list);
void				free_env_list(t_env *env_list);

//	pa_tokenizer
t_token				*create_token(char *value, int type);
void				add_token(t_token **token_list, t_token *new_token);
int					determine_type(char *token);
int					handle_quotes(t_tokenizer_state *state);
void				handle_double_greater(t_tokenizer_state *state);
int					handle_operator(t_tokenizer_state *state);
int					add_buffer_to_tokens(t_tokenizer_state *state);
int					process_input_char(t_tokenizer_state *state);
t_token				*tokenize_input(char *input);
void				print_tokens(t_token *tokens);

#endif