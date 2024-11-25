/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pa_free_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoyat <ngoyat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 23:58:04 by ngoyat            #+#    #+#             */
/*   Updated: 2024/11/25 04:52:05 by ngoyat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pa_header.h"

void	free_env_list(t_env_list *env_list)
{
	t_env	*current;
	t_env	*next;

	if (!env_list)
		return ;
	current = env_list->head;
	while (current)
	{
		next = current->next;
		free(current->key);
		free(current->value);
		free(current);
		current = next;
	}
	free(env_list);
}

// void	free_prompt(char *file, char *username, char *current_time)
// {
// 	free(file);
// 	free(username);
// 	free(current_time);
// }

// char	*get_dir(char *dir)
// {
// 	int		i;
// 	char	**split_dir;
// 	char	*file;

// 	split_dir = ft_split(dir, '/');
// 	if (!split_dir)
// 		return (NULL);
// 	i = 0;
// 	while (split_dir[i])
// 		i++;
// 	i--;
// 	file = ft_strjoin("-", split_dir[i]);
// 	while (i >= 0)
// 	{
// 		free(split_dir[i]);
// 		i--;
// 	}
// 	free(split_dir);
// 	return (file);
// }

// char	*get_file(void)
// {
// 	char	*file;
// 	char	*dir;

// 	dir = getcwd(NULL, 0);
// 	if (!dir)
// 	{
// 		perror("getcwd");
// 		return (NULL);
// 	}
// 	if (!ft_strncmp(dir, "/", ft_strlen(dir) + 1))
// 		file = ft_strdup("-/");
// 	else
// 		file = get_dir(dir);
// 	free(dir);
// 	return (file);
// }
