/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoyat <ngoyat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 19:32:14 by ngoyat            #+#    #+#             */
/*   Updated: 2024/11/23 20:51:31 by ngoyat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pa_header.h"

char	*ft_color_str(char *str, const char *color, char **to_free)
{
	char	*colored_str;
	char	*temp;

	temp = ft_strjoin(color, str);
	colored_str = ft_strjoin(temp, RS);
	free(temp);
	if (to_free && *to_free)
		free(*to_free);
	return (colored_str);
}

char	*get_username(t_env_list *env_list)
{
	t_env	*current;

	if (!env_list || !env_list->head)
		return ("no_user");
	current = env_list->head;
	while (current)
	{
		if (ft_strcmp(current->key, "USER") == 0)
			return (current->value);
		current = current->next;
	}
	return ("no_user");
}

char	*ft_format_username(t_env_list *env_list)
{
	char	*formatted_username;
	char	*blue_open;
	char	*blue_close;
	char	*colored_username;

	blue_open = ft_color_str("༺", BL, NULL);
	blue_close = ft_color_str("༻", BL, NULL);
	colored_username = ft_color_str(get_username(env_list), PU, NULL);
	if (!blue_open || !blue_close || !colored_username)
		return (NULL);
	formatted_username = ft_strjoin(blue_open, colored_username);
	formatted_username = ft_strjoin_free(formatted_username, blue_close);
	return (formatted_username);
}

char	*msh_prompt(t_env_list *env_list)
{
	char	*file;
	char	*username;
	char	*current_time;
	char	*prompt;
	char	*temp;

	file = ft_color_str(get_file(), CY, NULL);
	username = ft_format_username(env_list);
	current_time = ft_color_str(get_current_time(), GR, NULL);
	prompt = ft_strjoin(current_time, " ");
	temp = ft_strjoin(prompt, username);
	free(current_time);
	free(prompt);
	free(username);
	prompt = ft_strjoin(temp, " ");
	free(temp);
	temp = ft_strjoin(prompt, RD "᳀ " RS);
	free(prompt);
	if (env_list->debug % 2 != 0)
		prompt = ft_strjoin_free(temp, " [DEBUG MODE]");
	else
		prompt = temp;
	free(file);
	return (prompt);
}
