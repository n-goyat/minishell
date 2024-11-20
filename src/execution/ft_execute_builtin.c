/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_builtin.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maba <maba@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 14:56:47 by maba              #+#    #+#             */
/*   Updated: 2024/11/20 14:19:34 by maba             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ex_header.h"
#include "../includes/pa_header.h"

int	is_builtin(char **cmd)
{
	if (ft_strcmp(cmd[0], "cd") == 0 || ft_strcmp(cmd[0], "echo") == 0
		|| ft_strcmp(cmd[0], "exit") == 0 || ft_strcmp(cmd[0], "env") == 0
		|| ft_strcmp(cmd[0], "unset") == 0 || ft_strcmp(cmd[0], "export") == 0
		|| ft_strcmp(cmd[0], "pwd") == 0)
		return (1);
	return (0);
}

void	execute_builtin_command(t_cmd_node *cmd, t_env_list *env_list)
{
	(void)cmd;
	(void)env_list;
	if (ft_strcmp(cmd->cmd[0], "cd") == 0)
		builtin_cd(cmd->cmd, env_list);
	else if (ft_strcmp(cmd->cmd[0], "echo") == 0)
		builtin_echo(cmd->cmd);
	else if (ft_strcmp(cmd->cmd[0], "exit") == 0)
		builtin_exit(cmd->cmd, env_list);
	else if (ft_strcmp(cmd->cmd[0], "env") == 0)
		builtin_env(env_list);
	else if (ft_strcmp(cmd->cmd[0], "unset") == 0)
		builtin_unset(cmd->cmd, env_list);
	else if (ft_strcmp(cmd->cmd[0], "export") == 0)
		builtin_export(cmd->cmd, env_list);
	else if (ft_strcmp(cmd->cmd[0], "pwd") == 0)
		builtin_pwd();
}

void	ft_execute_builtin(t_cmd_node *cmd, t_env_list *env_list)
{
	int	in_fd;
	int	out_fd;
	int	saved_stdin;
	int	saved_stdout;

	in_fd = 0;
	out_fd = 1;
	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	dup(STDOUT_FILENO);
	handle_redirections(cmd, &in_fd, &out_fd);
	setup_file_descriptors(cmd, in_fd, out_fd);
	if (!env_list)
	{
		ft_putstr_fd("Environment list is NULL.\n", STDERR_FILENO);
		return ;
	}
	execute_builtin_command(cmd, env_list);
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdin);
	close(saved_stdout);
}
