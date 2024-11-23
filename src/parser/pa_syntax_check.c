/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoyat <ngoyat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 11:38:33 by maba              #+#    #+#             */
/*   Updated: 2024/11/23 05:37:09 by ngoyat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pa_header.h"

// Function to check for unmatched quotes in the input
int	quote_check(const char *input, int i)
{
	int	single_quotes;
	int	double_quotes;

	single_quotes = 0;
	double_quotes = 0;
	while (input[i] != '\0')
	{
		if (input[i] == '\'')
			single_quotes++;
		else if (input[i] == '\"')
			double_quotes++;
		i++;
	}
	if (single_quotes % 2 != 0)
	{
		perror("Syntax error: unmatched single quotes");
		return (1);
	}
	if (double_quotes % 2 != 0)
	{
		perror("Syntax error: unmatched double quotes");
		return (1);
	}
	return (0);
}

void	ft_check_debug(char *input, t_env_list *env_list)
{
	if (input && strcmp(input, "/debug") == 0)
	{
		env_list->debug += 1;
		if (env_list->debug % 2 != 0)
			printf("Debug mode ON\n");
		else
			printf("Debug mode OFF\n");
	}
}
