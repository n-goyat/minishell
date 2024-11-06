/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built-in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maba <maba@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 11:33:08 by maba              #+#    #+#             */
/*   Updated: 2024/10/21 11:42:27 by maba             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pa_header.h"

void	builtin_echo(char **args)
{
	int	i;

	i = 1;
	int newline = 1; // Par défaut, on ajoute une nouvelle ligne
	if (args[1] && ft_strcmp(args[1], "-n") == 0)
	{
		newline = 0; // Pas de nouvelle ligne si option -n est spécifiée
		i = 2;
	}
	while (args[i])
	{
		ft_putstr_fd(args[i], STDOUT_FILENO);
		if (args[i + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
		// Ajouter un espace entre les arguments
		i++;
	}
	if (newline)
		ft_putchar_fd('\n', STDOUT_FILENO);
	// Ajouter une nouvelle ligne si pas de -n
}

void	builtin_cd(char **args, t_env *env_list)
{
	char	*path;

	if (!args[1]) // Si aucun argument n'est donné, aller à HOME
	{
		path = ft_get_env("HOME", env_list);
		if (!path)
		{
			ft_putstr_fd("minishell: cd: HOME not set\n", STDERR_FILENO);
			return ;
		}
	}
	else
		path = args[1]; // Utiliser le chemin spécifié
	if (chdir(path) == -1)
		perror("cd");
}

void	builtin_pwd(void)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
		ft_putstr_fd(cwd, STDOUT_FILENO);
	else
		perror("pwd");
	ft_putchar_fd('\n', STDOUT_FILENO);
}

void	builtin_export(char **args, t_env_list *env_list)
{
	t_env	*temp;
	char	*key;
	char	*value;
	char	*delimiter;

	if (!args[1])
	{
		// Display all environment variables if no arguments are provided
		temp = env_list->head;
		while (temp)
		{
			ft_putstr_fd("declare -x ", STDOUT_FILENO);
			ft_putstr_fd(temp->key, STDOUT_FILENO);
			if (temp->value)
			{
				ft_putchar_fd('=', STDOUT_FILENO);
				ft_putchar_fd('"', STDOUT_FILENO);
				ft_putstr_fd(temp->value, STDOUT_FILENO);
				ft_putchar_fd('"', STDOUT_FILENO);
			}
			ft_putchar_fd('\n', STDOUT_FILENO);
			temp = temp->next;
		}
		return ;
	}
	// Parse key and value if argument contains '='
	delimiter = ft_strchr(args[1], '=');
	if (delimiter)
	{
		key = ft_strndup(args[1], delimiter - args[1]);
		value = ft_strdup(delimiter + 1);
	}
	else
	{
		key = ft_strdup(args[1]);
		value = NULL;
	}
	// Search for the key in the env_list
	temp = env_list->head;
	while (temp)
	{
		if (ft_strcmp(temp->key, key) == 0)
		{
			if (delimiter)
			{ // Update value if '=' was present
				free(temp->value);
				temp->value = value;
			}
			free(key);
			return ;
		}
		temp = temp->next;
	}
	// If key doesn’t exist, add it as a new node
	add_node(env_list, create_node_with_key_value(key, value));
	free(key);
}

void	builtin_unset(char **args, t_env **env_list)
{
	t_env	*prev;
	t_env	*current;

	prev = NULL;
	current = *env_list;
	if (!args[1])
	{
		ft_putstr_fd("unset: not enough arguments\n", STDERR_FILENO);
		return ;
	}
	while (current)
	{
		if (ft_strcmp(current->key, args[1]) == 0)
		{
			if (prev)
				prev->next = current->next;
			else
				*env_list = current->next;
			free(current->key);
			free(current->value);
			free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}

void	builtin_env(t_env *env_list)
{
	t_env	*current;

	current = env_list;
	while (current)
	{
		ft_putstr_fd(current->key, STDOUT_FILENO);
		ft_putchar_fd('=', STDOUT_FILENO);
		ft_putstr_fd(current->value, STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
		current = current->next;
	}
}

void	builtin_exit(char **args)
{
	int	exit_code;

	if (args[1])
	{
		exit_code = ft_atoi(args[1]);
		exit(exit_code);
	}
	else
	{
		exit(EXIT_SUCCESS);
	}
}
