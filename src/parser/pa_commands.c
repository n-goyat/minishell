/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pa_commands.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoyat <ngoyat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 15:40:49 by ngoyat            #+#    #+#             */
/*   Updated: 2024/10/22 13:39:18 by ngoyat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pa_header.h"

char	**dynamic_alloc(t_token **tokens)
{
	int		arg_count;
	char	**cmd;
	t_token	*current_token;

	arg_count = 0;
	current_token = *tokens;
	while (current_token && current_token->type != TOKEN_PIPE
		&& current_token->type != TOKEN_REDIRECT_IN
		&& current_token->type != TOKEN_REDIRECT_OUT
		&& current_token->type != TOKEN_HEREDOC
		&& current_token->type != TOKEN_APPEND)
	{
		arg_count++;
		current_token = current_token->next;
	}
	cmd = malloc(sizeof(char *) * (arg_count + 1));
	if (!cmd)
		return (NULL);
	return (cmd);
}

void	create_command(t_token **tokens, t_files_list *files_list,
		int file_type)
{
	add_file_node(files_list, create_file_node((*tokens)->next->value,
			file_type));
	*tokens = (*tokens)->next;
}

t_cmd_node	*parse_command(t_token **tokens, t_files_list **files_list,
		t_env_list *env_list)
{
	char	**cmd;
	int		arg_id;

	cmd = NULL;
	*files_list = init_files_list();
	cmd = dynamic_alloc(tokens);
	arg_id = 0;
	while (*tokens && (*tokens)->type != TOKEN_PIPE)
	{
		if ((*tokens)->type == TOKEN_REDIRECT_IN)
			create_command(tokens, *files_list, INFILE);
		else if ((*tokens)->type == TOKEN_REDIRECT_OUT)
			create_command(tokens, *files_list, OUTFILE);
		else if ((*tokens)->type == TOKEN_APPEND)
			create_command(tokens, *files_list, OUTFILE_APPEND);
		else if ((*tokens)->type == TOKEN_HEREDOC)
			create_command(tokens, *files_list, HEREDOC);
		else
			cmd[arg_id++] = expand_env_var(tokens, env_list, 0);
		*tokens = (*tokens)->next;
	}
	if (cmd)
		cmd[arg_id] = NULL;
	return (create_cmd_node(cmd, *files_list));
}

char	**ft_split_append(char **split, char *new_arg)
{
	int		i;
	char	**new_split;

	// Determine the size of the current split
	i = 0;
	while (split && split[i])
		i++;
	// Allocate space for the new array (+1 for new_arg, +1 for NULL terminator)
	new_split = malloc((i + 2) * sizeof(char *));
	if (!new_split)
		return (NULL);
	// Copy existing elements
	i = 0;
	while (split && split[i])
	{
		new_split[i] = split[i];
		i++;
	}
	// Add the new argument and NULL terminator
	new_split[i] = ft_strdup(new_arg);
	new_split[i + 1] = NULL;
	// Free old split if it exists
	if (split)
		free(split);
	return (new_split);
}

void	split_and_add_flags(char *arg, t_cmd_node *cmd_node)
{
	int		i;
	char	**temp;

	char flag[3]; // Single flag with a leading '-' and null terminator
	if (!arg || arg[0] != '-' || ft_strlen(arg) <= 2)
	{
		cmd_node->cmd = ft_split_append(cmd_node->cmd, arg); // Add as-is
		return ;
	}
	i = 1;
	while (arg[i])
	{
		flag[0] = '-';
		flag[1] = arg[i];
		flag[2] = '\0';
		temp = ft_split_append(cmd_node->cmd, flag); // Add single flag
		free(cmd_node->cmd);
		cmd_node->cmd = temp;
		i++;
	}
}
void	parse_and_group_commands(t_commands_list **cmd_list,
		t_token_list **token_list, t_env_list **env_list)
{
	t_files_list	*files_list;
	t_cmd_node		*cmd_node;
	t_token			*current_token;

	(*cmd_list) = init_commands_list();
	current_token = (*token_list)->head;
	while (current_token)
	{
		if (current_token->type == TOKEN_PIPE)
		{
			if (current_token->type == TOKEN_WORD)
				split_and_add_flags(current_token->value, cmd_node);
			if (current_token->next && current_token->next->type == TOKEN_PIPE)
			{
				printf("syntax error near unexpected token `|'\n");
				return ;
			}
			current_token = current_token->next;
		}
		else
		{
			cmd_node = parse_command(&current_token, &files_list, (*env_list));
			add_cmd_node(*cmd_list, cmd_node);
		}
	}
}
