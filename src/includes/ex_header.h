/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_header.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoyat <ngoyat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 17:18:15 by maba              #+#    #+#             */
/*   Updated: 2024/11/23 04:55:37 by ngoyat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EX_HEADER_H
# define EX_HEADER_H

# include "pa_header.h"

typedef struct s_pipeline_data
{
	t_cmd_node	*current;
	int			in_fd;
	int			pipefd[2];
	int			is_last_cmd;
	pid_t		pids[1024];
	int			cmd_index;
}				t_pipeline_data;

typedef struct s_path_data
{
	char		**paths;
	char		*path_env;
	char		*temp;
	char		*full_path;
	int			i;
}				t_path_data;

typedef struct s_merge_data
{
	char		**new_cmd;
	int			split_len;
	int			cmd_len;
	int			total_len;
	int			i;
}				t_merge_data;

typedef struct s_exec_data
{
	char		*cmd_path;
	char		**envp;
	int			in_fd;
	int			out_fd;
}				t_exec_data;

// builtin export functions
void			update_or_add_variable(t_env_list *env_list, char *key,
					char *value, int is_append);
void			concat_arguments(char **args, char **result);
void			remove_enclosing_quotes(char **str);
void			builtin_export(char **args, t_env_list *env_list);
void			print_all_variables(t_env_list *env_list);
void			parse_key_value_with_delimiter(char *arg, char **key,
					char **value);
void			parse_key_value(char *arg, char **key, char **value,
					int *is_append);

// find commande function
char			*get_path_env(t_env_list *env_list);
char			*build_full_path(const char *base_path, const char *command);
char			*search_command_in_paths(t_path_data *data,
					const char *command);
char			*find_command_in_path(char *command, t_env_list *env_list);

// execute pipeline function
void			initialize_pipeline(t_pipeline_data *data,
					t_commands_list *cmd_list);
void			setup_pipe(t_pipeline_data *data);
void			manage_descriptors(t_pipeline_data *data);
void			setup_child_descriptors(t_pipeline_data *data);
void			fork_and_execute_command(t_pipeline_data *data,
					t_env_list *env_list);
void			wait_for_all_processes(t_pipeline_data *data);
void			execute_pipeline(t_commands_list *cmd_list,
					t_env_list *env_list);
void			execute_individual_command(t_cmd_node *current,
					t_env_list *env_list);
void			handle_commands(t_commands_list *cmd_list,
					t_env_list *env_list);
void			handle_debug_command(t_cmd_node *cmd, t_env_list *env_list);

// execute command
t_exec_data		prepare_exec_data(t_cmd_node *cmd, t_env_list *env_list);
void			execute_command(t_exec_data data, t_cmd_node *cmd,
					t_env_list *env_list);
void			*ft_exit(t_env_list *env_list, int exit_code);
void			handle_command_not_found(const t_exec_data *data,
					t_cmd_node *cmd, t_env_list *env_list);

// execute command utils
char			*check_cmd(t_cmd_node *cmd, char *cmd_path);
char			*get_command_path(t_cmd_node *cmd, t_env_list *env_list);
char			**merge_arrays(char **split_result, char **cmd);
void			split_command_and_flags(t_cmd_node *cmd);

// handle files functions
void			fatal_error(const char *message);
void			handle_infile(t_file_node *file, int *in_fd);
void			handle_outfile(t_file_node *file, int *out_fd);
void			handle_outfile_append(t_file_node *file, int *out_fd);
void			handle_heredoc(t_file_node *file, int *in_fd);
void			process_file_node(t_file_node *file, int *in_fd, int *out_fd);

// execute built-in
int				is_builtin(char **cmd);
void			execute_builtin_command(t_cmd_node *cmd, t_env_list *env_list);
void			ft_execute_builtin(t_cmd_node *cmd, t_env_list *env_list);

void			*ft_exit(t_env_list *env_list, int exit_code);
#endif