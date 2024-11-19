/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_header.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maba <maba@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 17:18:15 by maba              #+#    #+#             */
/*   Updated: 2024/11/19 17:27:43 by maba             ###   ########.fr       */
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

#endif