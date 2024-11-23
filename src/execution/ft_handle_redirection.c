/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_redirection.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoyat <ngoyat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 14:57:08 by maba              #+#    #+#             */
/*   Updated: 2024/11/23 02:19:50 by ngoyat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pa_header.h"
#include "../includes/ex_header.h"

void	process_file_node(t_file_node *file, int *in_fd, int *out_fd)
{
	if (file->type == INFILE)
		handle_infile(file, in_fd);
	else if (file->type == OUTFILE)
		handle_outfile(file, out_fd);
	else if (file->type == OUTFILE_APPEND)
		handle_outfile_append(file, out_fd);
	else if (file->type == HEREDOC)
		handle_heredoc(file, in_fd);
}

void	handle_redirections(t_cmd_node *cmd, int *in_fd, int *out_fd)
{
	t_file_node	*file;

	file = cmd->files->head;
	while (file)
	{
		process_file_node(file, in_fd, out_fd);
		file = file->next;
	}
}

void	setup_file_descriptors(t_cmd_node *cmd, int in_fd, int out_fd)
{
	int	redir_in_fd;
	int	redir_out_fd;

	redir_in_fd = in_fd;
	redir_out_fd = out_fd;
	(void)cmd;
	if (redir_in_fd != STDIN_FILENO)
	{
		if (dup2(redir_in_fd, STDIN_FILENO) == -1)
		{
			perror("dup2 in_fd");
			exit(EXIT_FAILURE);
		}
		close(redir_in_fd);
	}
	if (redir_out_fd != STDOUT_FILENO)
	{
		if (dup2(redir_out_fd, STDOUT_FILENO) == -1)
		{
			perror("dup2 out_fd");
			exit(EXIT_FAILURE);
		}
		close(redir_out_fd);
	}
}
