/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_builtin.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maba <maba@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 14:56:47 by maba              #+#    #+#             */
/*   Updated: 2024/10/21 12:10:54 by maba             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pa_header.h"

/**
* ft_execute_builtin() : Gère l'exécution des commandes built-ins sans créer de processus enfant.
*
* Entrée : Un tableau de tokens.
* Utilise : Les fonctions spécifiques aux built-ins
*/

int is_builtin(char **cmd)
{
    if (ft_strcmp(cmd[0], "cd") == 0 || ft_strcmp(cmd[0], "echo") == 0 ||
        ft_strcmp(cmd[0], "exit") == 0 || ft_strcmp(cmd[0], "env") == 0 ||
        ft_strcmp(cmd[0], "unset") == 0 || ft_strcmp(cmd[0], "export") == 0 ||
        ft_strcmp(cmd[0], "pwd") == 0)
        return (1);
    return (0);
}

void ft_execute_builtin(t_cmd_node *cmd, t_env *env_list)
{
    if (ft_strcmp(cmd->cmd[0], "cd") == 0)
        builtin_cd(cmd->cmd, env_list);
    else if (ft_strcmp(cmd->cmd[0], "echo") == 0)
        builtin_echo(cmd->cmd);
    else if (ft_strcmp(cmd->cmd[0], "exit") == 0)
        builtin_exit(cmd->cmd);
    else if (ft_strcmp(cmd->cmd[0], "env") == 0)
        builtin_env(env_list);
    else if (ft_strcmp(cmd->cmd[0], "unset") == 0)
        builtin_unset(cmd->cmd, &env_list);
    else if (ft_strcmp(cmd->cmd[0], "export") == 0)
        builtin_export(cmd->cmd, &env_list);
    else if (ft_strcmp(cmd->cmd[0], "pwd") == 0)
        builtin_pwd();
}
