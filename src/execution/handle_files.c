/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_files.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maba <maba@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 19:57:55 by maba              #+#    #+#             */
/*   Updated: 2024/11/20 02:05:31 by maba             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ex_header.h"
#include "../includes/pa_header.h"

void	fatal_error(const char *message)
{
	perror(message);
	exit(EXIT_FAILURE);
}

void	handle_infile(t_file_node *file, int *in_fd)
{
	*in_fd = open(file->filename, O_RDONLY);
	if (*in_fd == -1)
		fatal_error("open INFILE");
}

void	handle_outfile(t_file_node *file, int *out_fd)
{
	*out_fd = open(file->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (*out_fd == -1)
		fatal_error("open OUTFILE");
}

void	handle_outfile_append(t_file_node *file, int *out_fd)
{
	*out_fd = open(file->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (*out_fd == -1)
		fatal_error("open OUTFILE_APPEND");
}

void	handle_heredoc(t_file_node *file, int *in_fd)
{
	*in_fd = here_doc(file->filename);
	if (*in_fd == -1)
		fatal_error("here_doc");
}
