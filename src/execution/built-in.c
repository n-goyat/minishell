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

	int newline = 1; // Default to adding a newline
	if (args[1] && ft_strcmp(args[1], "-n") == 0)
	{
		newline = 0; // Disable newline if "-n" is specified
		i = 2;
	}
	else
		i = 1;
	while (args[i])
	{
		ft_putstr_fd(args[i], STDOUT_FILENO);
		if (args[i + 1])
			ft_putchar_fd(' ', STDOUT_FILENO); // Add space between args
		i++;
	}
	if (newline)
		ft_putchar_fd('\n', STDOUT_FILENO); // Add newline if enabled
}

void	builtin_cd(char **args, t_env_list *env_list)
{
	char	*path;

	if (!args[1]) // Go to HOME if no argument is provided
	{
		path = ft_get_env("HOME", env_list);
		if (!path)
		{
			ft_putstr_fd("minishell: cd: HOME not set\n", STDERR_FILENO);
			return ;
		}
	}
	else
		path = args[1];
	if (chdir(path) == -1)
		perror("cd"); // Print error if chdir fails
}

void	builtin_pwd(void)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
		ft_putstr_fd(cwd, STDOUT_FILENO);
	else
		perror("pwd"); // Error if getcwd fails
	ft_putchar_fd('\n', STDOUT_FILENO);
}

// void	builtin_export(char **args, t_env_list *env_list)
// {
// 	t_env	*temp;
// 	char	*key;
// 	char	*value;
// 	char	*delimiter;

// 	if (!args[1]) // Print all variables if no arguments
// 	{
// 		temp = env_list->head;
// 		while (temp)
// 		{
// 			ft_putstr_fd("declare -x ", STDOUT_FILENO);
// 			ft_putstr_fd(temp->key, STDOUT_FILENO);
// 			if (temp->value != NULL)
// 			{
// 				ft_putchar_fd('=', STDOUT_FILENO);
// 				ft_putchar_fd('"', STDOUT_FILENO);
// 				ft_putstr_fd(temp->value, STDOUT_FILENO);
// 				ft_putchar_fd('"', STDOUT_FILENO);
// 			}
// 			ft_putchar_fd('\n', STDOUT_FILENO);
// 			temp = temp->next;
// 		}
// 		return ;
// 	}
// 	// Process key and value from argument
// 	delimiter = ft_strchr(args[1], '=');
// 	if (delimiter)
// 	{
// 		key = ft_strndup(args[1], delimiter - args[1]);
// 		value = ft_strdup(delimiter + 1);
// 	}
// 	else
// 	{
// 		key = ft_strdup(args[1]);
// 		value = NULL;
// 	}
// 	// Search for key in env_list, update if found
// 	temp = env_list->head;
// 	while (temp)
// 	{
// 		if (ft_strcmp(temp->key, key) == 0)
// 		{
// 			if (delimiter && value != NULL) // Update value if '=' present
// 			{
// 				free(temp->value);
// 				temp->value = value;
// 			}
// 			free(key);
// 			return ;
// 		}
// 		temp = temp->next;
// 	}
// 	// Add new key-value pair if not found
// 	add_node(env_list, create_node_with_key_value(key, value));
// 	free(key);
// }

void	builtin_unset(char **args, t_env_list *env_list)
{
	t_env	*prev;
	t_env	*current;

	prev = NULL;
	if (!args[1])
	{
		ft_putstr_fd("unset: not enough arguments\n", STDERR_FILENO);
		return ;
	}
	current = env_list->head;
	while (current)
	{
		if (ft_strcmp(current->key, args[1]) == 0)
		{
			if (prev)
				prev->next = current->next;
			else
				env_list->head = current->next;
			free(current->key);
			free(current->value);
			free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}

void	builtin_env(t_env_list *env_list)
{
	t_env	*current;

	if (!env_list)
	{
		fprintf(stderr, "Environment list is NULL.\n");
		return ;
	}
	current = env_list->head;
	while (current)
	{
		if (current->value != NULL && current->value[0] != '\0')
			printf("%s=%s\n", current->key, current->value);
		current = current->next;
	}
}

void	builtin_exit(char **args)
{
	int	exit_code;

	exit_code = 0;
	if (args[1])
	{
		if (ft_isdigit(ft_atoi(args[1])))
			exit_code = ft_atoi(args[1]);
		else
		{
			ft_putstr_fd("minishell: exit: numeric argument required\n",
				STDERR_FILENO);
			exit(255); // Exit with error code for invalid numeric
		}
	}
	exit(exit_code); // Exit with the provided code or 0
}
