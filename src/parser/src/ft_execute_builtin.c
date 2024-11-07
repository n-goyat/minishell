/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_builtin.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maba <maba@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 14:56:47 by maba              #+#    #+#             */
/*   Updated: 2024/11/02 14:19:17 by maba             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pa_header.h"

/**

	* ft_execute_builtin() : Gère l'exécution des commandes built-ins sans créer de processus enfant.
 *
 * Entrée : Un tableau de tokens.
 * Utilise : Les fonctions spécifiques aux built-ins
 */

int	is_builtin(char **cmd)
{
	if (ft_strcmp(cmd[0], "cd") == 0 || ft_strcmp(cmd[0], "echo") == 0
		|| ft_strcmp(cmd[0], "exit") == 0 || ft_strcmp(cmd[0], "env") == 0
		|| ft_strcmp(cmd[0], "unset") == 0 || ft_strcmp(cmd[0], "export") == 0
		|| ft_strcmp(cmd[0], "pwd") == 0)
		return (1);
	return (0);
}

void	ft_execute_builtin(t_cmd_node *cmd, t_env_list *env_list)
{
	int	in_fd;
	int	out_fd;
	int	saved_stdin;
	int	saved_stdout;

	in_fd = 0;
	out_fd = 1;
	// Sauvegarder les descripteurs d'origine
	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	dup(STDOUT_FILENO);
	ft_handle_redirections(cmd, &in_fd, &out_fd, NULL, NULL);
	// debug
	if (!env_list)
	{
		fprintf(stderr, "Environment list is NULL.\n");
		return ;
	}
	// Exécuter le builtin
	if (ft_strcmp(cmd->cmd[0], "cd") == 0)
		builtin_cd(cmd->cmd, env_list); // todo (t_env_list)
	else if (ft_strcmp(cmd->cmd[0], "echo") == 0)
		builtin_echo(cmd->cmd);
	else if (ft_strcmp(cmd->cmd[0], "exit") == 0)
		builtin_exit(cmd->cmd);
	else if (ft_strcmp(cmd->cmd[0], "env") == 0)
		builtin_env(env_list);
	else if (ft_strcmp(cmd->cmd[0], "unset") == 0)
		builtin_unset(cmd->cmd, env_list);
	else if (ft_strcmp(cmd->cmd[0], "export") == 0)
		builtin_export(cmd->cmd, env_list);
	else if (ft_strcmp(cmd->cmd[0], "pwd") == 0)
		builtin_pwd();
	// Restaurer les descripteurs d'origine
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	// Fermer les descripteurs sauvegardés
	close(saved_stdin);
	close(saved_stdout);
}
