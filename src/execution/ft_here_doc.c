/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maba <maba@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 02:35:12 by maba              #+#    #+#             */
/*   Updated: 2024/11/19 18:30:47 by maba             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pa_header.h"

int	ft_error_open_file(int fd)
{
	if (fd < 0)
		perror("open");
	return (-1);
}

int	read_in_stdin(char *delimiter, int fd)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	return (0);
}

// Fonction here_doc principale
int	here_doc(char *delimiter)
{
	int	tmp_fd;

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
