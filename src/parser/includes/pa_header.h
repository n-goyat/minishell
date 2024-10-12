/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pa_header.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoyat <ngoyat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 17:41:05 by ngoyat            #+#    #+#             */
/*   Updated: 2024/10/11 18:58:06 by ngoyat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PA_HEADER_H
# define PA_HEADER_H

# include "./libft/libft.h"
# include <ctype.h>
# include <limits.h>
# include <stdarg.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

//	pa_main_env_creation
t_env				*create_node(char *env_var);
void				add_node(t_env **env_list, t_env *new_node);
t_env				*init_env_list(char **env);
void				print_env_list(t_env *env_list);
void				free_env_list(t_env *env_list);

#endif