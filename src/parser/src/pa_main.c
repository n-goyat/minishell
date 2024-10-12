/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pa_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoyat <ngoyat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 17:41:11 by ngoyat            #+#    #+#             */
/*   Updated: 2024/10/11 19:58:58 by ngoyat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pa_header.h"

//temporary

// size_t	ft_strlen(const char *str)
// {
// 	size_t	i;

// 	i = 0;
// 	while (str[i] != '\0')
// 		i++;
// 	return (i);
// }
// char	*ft_strchr(const char *str, int c)
// {
// 	int	i;

// 	i = 0;
// 	while (str[i] != '\0')
// 	{
// 		if (str[i] == (char)c)
// 			return ((char *)(str + i));
// 		i++;
// 	}
// 	if (str[i] == (char)c)
// 		return ((char *)&str[i]);
// 	return (NULL);
// }

// char	*ft_strndup(const char *s, size_t n)
// {
// 	char			*res;
// 	unsigned int	i;

// 	i = 0;
// 	res = malloc(sizeof(char) * (n + 1));
// 	if (res == NULL)
// 		return (NULL);
// 	while (i < n)
// 	{
// 		res[i] = s[i];
// 		i++;
// 	}
// 	res[i] = '\0';
// 	return (res);
// }
// char	*ft_strdup(const char *s1)
// {
// 	char	*tmp;
// 	size_t	i;

// 	i = 0;
// 	tmp = (char *)malloc(ft_strlen(s1) + 1);
// 	if (!tmp)
// 		return (NULL);
// 	while (s1[i])
// 	{
// 		tmp[i] = s1[i];
// 		i++;
// 	}
// 	tmp[i] = 0;
// 	return (tmp);
// }
//temporary

t_env	*create_node(char *env_var)
{
	t_env	*new_node;
	char	*delimiter;

	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	delimiter = ft_strchr(env_var, '=');
	if (!delimiter)
		return (NULL);
	new_node->key = ft_strndup(env_var, delimiter - env_var);
	new_node->value = ft_strdup(delimiter + 1);
	new_node->next = NULL;
	return (new_node);
}

void	add_node(t_env **env_list, t_env *new_node)
{
	t_env	*temp;

	temp = *env_list;
	if (*env_list == NULL)
	{
		*env_list = new_node;
		return ;
	}
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = new_node;
}

t_env	*init_env_list(char **env)
{
	t_env	*env_list;
	t_env	*new_node;
	int		i;

	env_list = NULL;
	i = 0;
	while (env[i] != NULL)
	{
		new_node = create_node(env[i]);
		if (new_node != NULL)
			add_node(&env_list, new_node);
		i++;
	}
	return (env_list);
}

void	print_env_list(t_env *env_list)
{
	t_env	*temp;

	temp = env_list;
	while (temp != NULL)
	{
		printf("%s=%s\n", temp->key, temp->value);
		// printf("key: %s\n", tmp->key);
		// printf("value: %s\n", tmp->value);
		temp = temp->next;
	}
}

void	free_env_list(t_env *env_list)
{
	t_env	*temp;

	while (env_list != NULL)
	{
		temp = env_list;
		env_list = env_list->next;
		free(temp->key);
		free(temp->value);
		free(temp);
	}
}

int	main(int ac, char **av, char **env)
{
	t_env	*env_list;

	(void)ac;
	(void)av;
	env_list = init_env_list(env);
	print_env_list(env_list);
	free_env_list(env_list);
	return (0);
}
