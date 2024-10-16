/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pa_header.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoyat <ngoyat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 17:41:05 by ngoyat            #+#    #+#             */
/*   Updated: 2024/10/16 14:49:21 by ngoyat           ###   ########.fr       */
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
	char				*key;
	char				*value;
	struct s_env		*next;
}						t_env;

// Tekonization structs
typedef struct s_token
{
	int					type;
	char				*value;
	struct s_token		*next;
}						t_token;

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIRECT_IN,
	TOKEN_REDIRECT_OUT,
	TOKEN_APPEND,
	TOKEN_HEREDOC,
	TOKEN_SIN_QOTES,
	TOKEN_DBL_QOTES,
	TOKEN_OTHER,
}						t_token_type;

// File structs
typedef struct s_file_node
{
	char				*input_file;
	char				*output_file;
	int append; // 1 for append (>>), 0 for overwrite (>)
	char				*heredoc;
	struct s_file_node	*next;
}						t_file_node;

typedef struct s_files_list
{
	t_file_node			*head;
	t_file_node			*tail;
	size_t				size;
}						t_files_list;

// Command structs
typedef enum e_cmd_type
{
	CMD_SIMPLE,       // Simple command
	CMD_PIPE,         // Piping (|)
	CMD_AND,          // Logical AND (&&)
	CMD_OR,           // Logical OR (||)
	CMD_REDIRECT_IN,  // Redirect input (<)
	CMD_REDIRECT_OUT, // Redirect output (>)
	CMD_APPEND_OUT    // Append output (>>)
}						t_cmd_type;

typedef struct s_cmd_node
{
	int					type;
	t_files_list		*files;
	char				**cmd;
	struct s_cmd_node	*next;
}						t_cmd_node;

typedef struct s_commands_list
{
	t_cmd_node			*head;
	t_cmd_node			*tail;
	size_t				size;
}						t_commands_list;

//	pa_main_env_creation
t_env					*create_node(char *env_var);
void					add_node(t_env **env_list, t_env *new_node);
t_env					*init_env_list(char **env);
void					print_env_list(t_env *env_list);
void					free_env_list(t_env *env_list);

//	pa_tokenizer
t_token					*create_token(char *value, int type);
void					add_token(t_token **token_list, t_token *new_token);
int						determine_type(char *token);
void					print_tokens(t_token *tokens);
int						word_len(char *word);
int						write_token(char *in, int *i, t_token *token,
							t_token_type typ);
int						handle_quotes(char *in, t_token *token,
							t_token_type typ);
int						assign_token_typ(char *in, int *i, t_token *token);
t_token					*tokenize_input(char *in);

#endif