/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pa_header.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maba <maba@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 17:53:26 by maba              #+#    #+#             */
/*   Updated: 2024/11/12 23:25:19 by maba             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PA_HEADER_H
# define PA_HEADER_H
# include "./libft/libft.h"
# include <ctype.h>
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <signal.h>
# include <stdarg.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <readline/history.h>
# include <readline/readline.h>

// Env structs
typedef struct s_env
{
	char				*key;
	char				*value;
	struct s_env		*next;
}						t_env;

typedef struct s_env_list
{
	t_env				*head;
	t_env				*tail;
	int					size;
}						t_env_list;

// Tokenization structs
typedef struct s_token
{
	int					type;
	char				*value;
	int					position;
	struct s_token		*next;
}						t_token;

typedef struct s_token_list
{
	t_token				*head;
	t_token				*tail;
	int					size;
}						t_token_list;

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
	char				*filename;
	int					type;
	int					processed;
	struct s_file_node	*next;
}						t_file_node;

typedef struct s_files_list
{
	t_file_node			*head;
	t_file_node			*tail;
	int					size;
}						t_files_list;

typedef enum e_file_type
{
	INFILE,
	OUTFILE,
	OUTFILE_APPEND,
	HEREDOC,
}						t_file_type;

// Command structs
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

typedef enum e_cmd_type
{
	CMD_SIMPLE,
	CMD_PIPE,
	CMD_AND,
	CMD_OR,
	CMD_REDIRECT_IN,
	CMD_REDIRECT_OUT,
	CMD_APPEND_OUT
}						t_cmd_type;

// debug.c
void					print_tokens(t_token_list *token_list);
void					print_cmd_args(char **cmd);
void					print_cmd_files(t_files_list *files);
void					print_cmd_list(t_commands_list *cmd_list);
void					print_cmd_list(t_commands_list *cmd_list);
void					print_env_list(t_env_list *env_list);

// pa_commands functions
char					**dynamic_alloc(t_token **tokens);
void					create_command(t_token **tokens,
							t_files_list *files_list, int file_type);
t_cmd_node				*parse_command(t_token **tokens,
							t_files_list **files_list, t_env_list *env_list);
void					parse_and_group_commands(t_commands_list **cmd_list,
							t_token_list **token_list, t_env_list **env_list);

// pa_env_expander_utils.c
char					*ft_strjoin_free(char *s1, const char *s2);
char					**split_and_free(char *str, char *delim);
char					*append_character(char *result, char c);
int						inside_single_quotes(const char *str, int pos);

// pa_env_expander functions
char					*get_env_value(char *env_name, t_env_list *env_list);
char					*expand_single_variable(const char *str, int *i,
							t_env_list *env_list);
char					*expand_variable(char *value, int *i,
							t_env_list *env_list, char *result);

char					*expand_env_var(t_token **token, t_env_list *env_list,
							int i);
char					*quotes(t_token **token);

// pa_free functions
void					free_token_list(t_token_list *token_list);
void					free_cmd_node(t_cmd_node *cmd_node);
void					free_cmd_list(t_commands_list *cmd_list);
void					free_env_list(t_env_list *env_list);

// pa_init.c functions
t_files_list			*init_files_list(void);
t_commands_list			*init_commands_list(void);
t_token_list			*init_token_list(void);
void					init_env_list_from_envp(t_env_list *env_list,
							char **envp);
t_env_list				*init_env_list(char **envp);

// pa_tokenizer_2 functions
void					expand_token_value(t_token *token,
							t_env_list *env_list);

// pa_tokenizer_utils functions
int						ft_word_len(char *word);
int						needs_space(t_token *current, t_token *next,
							const char *input);
void					finalize_token_list(t_token_list *token_list,
							const char *input);
void					skip_whitespace(char *in, int *i);
void					concatenate_tokens(t_token *current,
							t_token *next_token, char *new_value);
// pa_tokenizer functions
int						write_token(char *in, int *i, t_token *token,
							t_token_type typ);
int						handle_quotes(char *in, t_token *token,
							t_token_type typ);

int						assign_token_typ(char *in, int *i, t_token *token,
							t_env_list *env_list);
t_token_list			*tokenize_input(char *in, t_env_list *env_list);

// pa_utils_add functions
void					add_token(t_token_list *token_list, t_token *new_token);
void					add_cmd_node(t_commands_list *cmd_list,
							t_cmd_node *new_node);
void					add_file_node(t_files_list *files_list,
							t_file_node *new_file);
void					add_node(t_env_list *env_list, t_env *new_node);

// pa_utils_create functions
t_token					*create_token(char *value, int type);
t_cmd_node				*create_cmd_node(char **cmd, t_files_list *files_list);
t_file_node				*create_file_node(char *filename, int type);
t_env					*create_node(char *env_var);
t_env					*create_node_with_key_value(char *key, char *value);
t_env	*create_exit_code_node(void);

// Exécution des commandes
void					ft_execute_command(t_cmd_node *cmd,
							t_env_list *env_list);
void					ft_execute_builtin(t_cmd_node *cmd,
							t_env_list *env_list);
int						is_builtin(char **cmd);
void					execute_pipeline(t_commands_list *cmd_list,
							t_env_list *env_list);
void					handle_commands(t_commands_list *cmd_list,
							t_env_list *env_list);
void					fork_and_execute(t_cmd_node *cmd, t_env_list *env_list,
							int in_fd, int out_fd);
void					execute_single_command(t_cmd_node *cmd,
							t_env_list *env_list);
void					execute_command(t_cmd_node *cmd, char *cmd_path,
							char **envp);

// Gestion des processus
void					ft_wait_for_processes(pid_t pid);

// Gestion des variables d'environnement
char					**ft_copy_env(t_env_list *env_list);
char					*ft_get_env(char *key, t_env_list *env_list);
char					*find_command_in_path(char *command,
							t_env_list *env_list);

// Built-ins
void					builtin_echo(char **args);
void					builtin_cd(char **args, t_env_list *env_list);
void					builtin_pwd(void);
void					builtin_export(char **args, t_env_list *env_list);
void					builtin_unset(char **args, t_env_list *env_list);
void					builtin_env(t_env_list *env_list);
void					builtin_exit(char **args);

// fonction de gestion des HEREDOC et Redirection
void					ft_handle_redirections(t_cmd_node *cmd, int *in_fd,
							int *out_fd, char *cmd_path, char **envp);
int						ft_check_files(t_files_list *files_list, int *in_fd,
							int *out_fd);
int						here_doc(char *delimiter);

// utiles fonctions
int						ft_strncmp(const char *s1, const char *s2, size_t n);
int						ft_strcmp(char *s1, char *s2);
void					free_split(char **split);

#endif