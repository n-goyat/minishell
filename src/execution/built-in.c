/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built-in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maba <maba@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 11:33:08 by maba              #+#    #+#             */
/*   Updated: 2024/11/20 02:50:07 by maba             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ex_header.h"
#include "../includes/pa_header.h"

void	builtin_unset(char **args, t_env_list *env_list)
{
	t_env_traversal	traversal;

	if (!args[1])
	{
		ft_putstr_fd("unset: not enough arguments\n", STDERR_FILENO);
		return ;
	}
	traversal.prev = NULL;
	traversal.current = env_list->head;
	while (traversal.current)
	{
		if (ft_strcmp(traversal.current->key, args[1]) == 0)
		{
			if (traversal.prev)
				traversal.prev->next = traversal.current->next;
			else
				env_list->head = traversal.current->next;
			free(traversal.current->key);
			free(traversal.current->value);
			free(traversal.current);
			return ;
		}
		traversal.prev = traversal.current;
		traversal.current = traversal.current->next;
	}
}

void	builtin_env(t_env_list *env_list)
{
	t_env	*current;

	if (!env_list)
	{
		ft_putstr_fd("Environment list is NULL.\n", STDERR_FILENO);
		return ;
	}
	current = env_list->head;
	while (current)
	{
		if (current->value != NULL && current->value[0] != '\0'
			&& current->key[0] != '?')
			printf("%s=%s\n", current->key, current->value);
		current = current->next;
	}
}

int	exit_numeric(char *argv)
{
	int	exit_code;

	exit_code = 0;
	if (ft_isdigit(ft_atoi(argv)) == 1)
		exit_code = ft_atoi(argv);
	else
	{
		ft_putstr_fd("minishell: exit: numeric argument required\n",
			STDERR_FILENO);
		exit(255);
	}
	return (exit_code);
}

void	builtin_exit(char **args, t_env_list *env_list)
{
	int		exit_code;
	int		i;
	t_env	*current;

	current = env_list->head;
	i = -1;
	while (++i < (env_list->size) && current)
	{
		if (ft_strncmp(current->key, "SHLVL", ft_strlen(current->key)) == 0)
		{
			free(current->value);
			current->value = ft_itoa(ft_atoi(current->value) - 1);
			break ;
		}
		current = current->next;
	}
	exit_code = 0;
	if (args[1])
		exit_code = exit_numeric(args[1]);
	exit(exit_code);
}
