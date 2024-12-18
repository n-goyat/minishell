/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoyat <ngoyat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 20:39:26 by maba              #+#    #+#             */
/*   Updated: 2024/11/24 21:34:49 by ngoyat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ex_header.h"
#include "../includes/pa_header.h"

char	*get_path_env(t_env_list *env_list)
{
	char	*path_env;

	path_env = ft_get_env("PATH", env_list);
	if (!path_env)
		ft_putstr_fd("get_path_env: PATH is NULL\n", STDERR_FILENO);
	return (path_env);
}

char	*build_full_path(char *base_path, char *command)
{
	char	*temp;
	char	*full_path;

	temp = ft_strjoin(base_path, "/");
	if (!temp)
	{
		ft_putstr_fd("build_full_path: ft_strjoin failed\n", STDERR_FILENO);
		return (NULL);
	}
	full_path = ft_strjoin(temp, command);
	free(temp);
	if (!full_path)
		ft_putstr_fd("build_full_path: ft_strjoin failed\n", STDERR_FILENO);
	return (full_path);
}

char	*search_command_in_paths(t_path_data *data, char *command)
{
	while (data->paths[data->i])
	{
		data->full_path = build_full_path(data->paths[data->i], command);
		if (!data->full_path)
		{
			free_split(data->paths);
			return (NULL);
		}
		if (access(data->full_path, X_OK) == 0)
		{
			free_split(data->paths);
			return (data->full_path);
		}
		free(data->full_path);
		data->i++;
	}
	return (NULL);
}

char	*find_command_in_path(char *command, t_env_list *env_list)
{
	t_path_data	data;

	data.path_env = get_path_env(env_list);
	if (!data.path_env)
		return (NULL);
	data.paths = ft_split(data.path_env, ':');
	if (!data.paths)
	{
		ft_putstr_fd("find_command_in_path: ft_split failed\n", STDERR_FILENO);
		return (NULL);
	}
	data.i = 0;
	data.full_path = search_command_in_paths(&data, command);
	if (data.full_path)
		return (data.full_path);
	free_split(data.paths);
	return (NULL);
}
