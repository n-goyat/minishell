
#include "../includes/pa_header.h"

t_env	*create_exit_code_node(void)
{
	t_env	*new_node;

	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	new_node->key = ft_strdup("?");
	new_node->value = ft_strdup("0");
	new_node->next = NULL;
	return (new_node);
}

// char	**ft_split_append(char **split, char *new_arg)
// {
// 	int		i;
// 	char	**new_split;

// 	i = 0;
// 	while (split && split[i])
// 		i++;
// 	new_split = malloc((i + 2) * sizeof(char *));
// 	if (!new_split)
// 		return (NULL);
// 	i = 0;
// 	while (split && split[i])
// 	{
// 		new_split[i] = split[i];
// 		i++;
// 	}
// 	new_split[i] = ft_strdup(new_arg);
// 	new_split[i + 1] = NULL;
// 	if (split)
// 		free(split);
// 	return (new_split);
// }

// void	split_and_add_flags(char *arg, t_cmd_node *cmd_node)
// {
// 	int		i;
// 	char	**temp;
// 	char	flag[3];

// 	if (!arg || arg[0] != '-' || ft_strlen(arg) <= 2)
// 	{
// 		cmd_node->cmd = ft_split_append(cmd_node->cmd, arg);
// 		return ;
// 	}
// 	i = 1;
// 	while (arg[i])
// 	{
// 		flag[0] = '-';
// 		flag[1] = arg[i];
// 		flag[2] = '\0';
// 		temp = ft_split_append(cmd_node->cmd, flag);
// 		free(cmd_node->cmd);
// 		cmd_node->cmd = temp;
// 		i++;
// 	}
// }
