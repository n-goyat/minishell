/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoyat <ngoyat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 20:35:28 by ngoyat            #+#    #+#             */
/*   Updated: 2024/11/23 20:43:56 by ngoyat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pa_header.h"

char	*get_current_time(void)
{
	time_t		rawtime;
	struct tm	*timeinfo;
	char		*formatted_time;

	rawtime = time(NULL);
	if (rawtime == -1)
		return (ft_strdup("00:00"));
	timeinfo = localtime(&rawtime);
	if (!timeinfo)
		return (ft_strdup("00:00"));
	formatted_time = malloc(9);
	if (!formatted_time)
		return (NULL);
	if (strftime(formatted_time, 9, "%H:%M:%S", timeinfo) == 0)
	{
		free(formatted_time);
		return (ft_strdup("00:00"));
	}
	return (formatted_time);
}
