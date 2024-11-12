/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoyat <ngoyat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:52:08 by ngoyat            #+#    #+#             */
/*   Updated: 2024/03/18 17:52:12 by ngoyat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*current;
	t_list	*next_node;

	current = lst;
	if (!lst || !f)
		return ;
	while (current->next != NULL)
	{
		next_node = current->next;
		f(current->content);
		current = next_node;
	}
	f(current->content);
}
