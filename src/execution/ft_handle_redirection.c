/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_redirection.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maba <maba@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 14:57:08 by maba              #+#    #+#             */
/*   Updated: 2024/11/12 22:54:49 by maba             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pa_header.h"

void fatal_error(const char *message) 
{
    perror(message);
    exit(EXIT_FAILURE);
}

void handle_redirections(t_cmd_node *cmd, int *in_fd, int *out_fd) 
{
    t_file_node *file = cmd->files->head;

    while (file) 
	{
        if (file->type == INFILE) 
        {
            *in_fd = open(file->filename, O_RDONLY);
            if (*in_fd == -1) 
                fatal_error("open INFILE");
        } 
		else if (file->type == OUTFILE) 
		{
            *out_fd = open(file->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (*out_fd == -1) 
                fatal_error("open OUTFILE");
        } 
		else if (file->type == OUTFILE_APPEND) 
		{
            *out_fd = open(file->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
            if (*out_fd == -1) 
                fatal_error("open OUTFILE_APPEND");
        } 
		else if (file->type == HEREDOC) 
		{
            *in_fd = here_doc(file->filename);
            if (*in_fd == -1) 
                fatal_error("here_doc");
        }
        file = file->next;
    }
}

void setup_file_descriptors(t_cmd_node *cmd, int in_fd, int out_fd) 
{
    int redir_in_fd = in_fd;
    int redir_out_fd = out_fd;

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
