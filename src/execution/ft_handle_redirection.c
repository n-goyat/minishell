/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_redirection.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maba <maba@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 14:57:08 by maba              #+#    #+#             */
/*   Updated: 2024/11/12 18:42:53 by maba             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pa_header.h"

/**
* ft_handle_redirection() : Gère l'ouverture des fichiers et la redirection des descripteurs de fichiers pour les redirections (>, >>, <).
*
*
*/

void	ft_handle_redirections(t_cmd_node *cmd, int *in_fd, int *out_fd,
		char *cmd_path, char **envp)
{
	if (cmd->files && ft_check_files(cmd->files, in_fd, out_fd) == -1)
	{
		free(cmd_path);
		free(envp);
		exit(EXIT_FAILURE);
	}
	// Rediriger stdin (entrée)
	if (*in_fd != 0)
	{
		if (dup2(*in_fd, STDIN_FILENO) == -1)
		{
			perror("dup2 in_fd");
			free(cmd_path);
			free(envp);
			close(*in_fd);
			exit(EXIT_FAILURE);
		}
		close(*in_fd);
	}
	// Rediriger stdout (sortie)
	if (*out_fd != 1)
	{
		if (dup2(*out_fd, STDOUT_FILENO) == -1)
		{
			perror("dup2 out_fd");
			free(cmd_path);
			free(envp);
			close(*out_fd);
			exit(EXIT_FAILURE);
		}
		close(*out_fd);
	}
}
