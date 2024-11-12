/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maba <maba@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 02:35:12 by maba              #+#    #+#             */
/*   Updated: 2024/11/04 16:50:18 by maba             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pa_header.h"

static int	ft_error_open_file(int fd)
{
	if (fd < 0)
		perror("open");
	return (-1);
}

static int	read_in_stdin(char *delimiter, int fd)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			fprintf(stderr,
				"warning: here-document delimited by end-of-file (wanted '%s')\n",
				delimiter);
			break ;
		}
		if (ft_strcmp(line, delimiter) == 0)
		{
			printf("delim: %s\n", line);
			free(line);
			break ;
		}
		printf("line: %s\n", line);
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	printf("reached end\n");
	return (0);
}

// Fonction here_doc principale
int	here_doc(char *delimiter)
{
	int	tmp_fd;

	printf("Opening .heredoc_tmp for writing\n");
	tmp_fd = open(".heredoc_tmp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (tmp_fd < 0)
		return (ft_error_open_file(tmp_fd));
	if (read_in_stdin(delimiter, tmp_fd) == -1)
	{
		close(tmp_fd);
		unlink(".heredoc_tmp");
		return (-1);
	}
	close(tmp_fd);
	tmp_fd = open(".heredoc_tmp", O_RDONLY);
	if (tmp_fd < 0)
	{
		ft_error_open_file(tmp_fd);
		unlink(".heredoc_tmp");
		return (-1);
	}
	unlink(".heredoc_tmp");
	return (tmp_fd);
}
// Function to handle opening of output files
int	handle_output_file(char *filename, int flags, mode_t mode)
{
	int	fd;

	fd = open(filename, flags, mode);
	if (fd == -1)
	{
		perror("open");
		return (-1);
	}
	return (fd);
}
// Updated ft_check_files function
int	ft_check_files(t_files_list *files_list, int *in_fd, int *out_fd)
{
	t_file_node	*current;

	current = files_list->head;
	while (current)
	{
		printf("Checking file:%s of type: %d\n ", current->filename,
			current->type);
		if (current->processed)
		{
			current = current->next;
			continue ;
		}
		if (current->type == INFILE)
		{
			*in_fd = open(current->filename, O_RDONLY);
			if (*in_fd == -1)
				return (ft_error_open_file(*in_fd));
		}
		else if (current->type == OUTFILE)
		{
			*out_fd = handle_output_file(current->filename,
					O_TRUNC | O_CREAT | O_RDWR, 0644);
			if (*out_fd == -1)
				return (ft_error_open_file(*out_fd));
		}
		else if (current->type == OUTFILE_APPEND)
		{
			*out_fd = handle_output_file(current->filename,
					O_APPEND | O_CREAT | O_RDWR, 0644);
			if (*out_fd == -1)
				return (ft_error_open_file(*out_fd));
		}
		else if (current->type == HEREDOC)
		{
			printf("Calling here_doc for delimiter:%s\n ", current->filename);
			*in_fd = here_doc(current->filename);
			if (*in_fd == -1)
				return (-1);
			current->processed = 1;
		}
		current = current->next;
	}
	return (0);
}
