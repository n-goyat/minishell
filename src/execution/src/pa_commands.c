/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pa_commands.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maba <maba@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 15:40:49 by ngoyat            #+#    #+#             */
/*   Updated: 2024/10/22 15:26:34 by maba             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pa_header.h"

t_cmd_node	*create_cmd_node(char **cmd, t_files_list *files_list)
{
	t_cmd_node	*new_node;

	new_node = malloc(sizeof(t_cmd_node));
	if (!new_node)
		return (NULL);
	new_node->cmd = cmd;
	new_node->files = files_list;
	new_node->next = NULL;
	return (new_node);
}

t_cmd_node	*create_pipe_node(void)
{
	t_cmd_node	*pipe_cmd;
	char		**cmd;

	pipe_cmd = malloc(sizeof(t_cmd_node));
	if (!pipe_cmd)
		return (NULL);
	cmd = malloc(sizeof(char *) * 2);
	if (!cmd)
	{
		free(pipe_cmd);
		return (NULL);
	}
	cmd[0] = ft_strdup("|");
	cmd[1] = NULL;
	pipe_cmd->cmd = cmd;
	pipe_cmd->files = NULL;
	pipe_cmd->next = NULL;
	return (pipe_cmd);
}

t_files_list	*init_files_list(void)
{
	t_files_list	*files_list;

	files_list = malloc(sizeof(t_files_list));
	if (!files_list)
		return (NULL);
	files_list->head = NULL;
	files_list->tail = NULL;
	files_list->size = 0;
	return (files_list);
}

t_commands_list	*init_commands_list(void)
{
	t_commands_list	*cmd_list;

	cmd_list = malloc(sizeof(t_commands_list));
	if (!cmd_list)
		return (NULL);
	cmd_list->head = NULL;
	cmd_list->tail = NULL;
	cmd_list->size = 0;
	return (cmd_list);
}

t_file_node	*create_file_node(char *filename, int type)
{
	t_file_node	*new_node;

	new_node = malloc(sizeof(t_file_node));
	if (!new_node)
		return (NULL);
	new_node->filename = ft_strdup(filename);
	new_node->type = type;
	new_node->next = NULL;
	return (new_node);
}

void	add_file_node(t_files_list *files_list, t_file_node *new_file)
{
	if (!files_list || !new_file)
		return ;
	if (!files_list->head)
	{
		files_list->head = new_file;
		files_list->tail = new_file;
	}
	else
	{
		files_list->tail->next = new_file;
		files_list->tail = new_file;
	}
	files_list->size++;
}

void	add_cmd_node(t_commands_list *cmd_list, t_cmd_node *new_node)
{
	if (!new_node)
		return ;
	if (!cmd_list->head)
	{
		cmd_list->head = new_node;
		cmd_list->tail = new_node;
	}
	else
	{
		cmd_list->tail->next = new_node;
		cmd_list->tail = new_node;
	}
	cmd_list->size++;
}

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

t_cmd_node	*parse_command(t_token **tokens, t_files_list **files_list,
		t_env *env_list)
{
	t_cmd_node	*cmd_node;
	char		**cmd;
	int			arg_id;

	(*files_list) = init_files_list();
	cmd = dynamic_alloc(tokens);
	arg_id = 0;
	while (*tokens && (*tokens)->type != TOKEN_PIPE)
	{
		if ((*tokens)->type == TOKEN_REDIRECT_IN)
			add_file_node((*files_list),
				create_file_node((*tokens)->next->value, INFILE));
		else if ((*tokens)->type == TOKEN_REDIRECT_OUT)
			add_file_node((*files_list),
				create_file_node((*tokens)->next->value, OUTFILE));
		else if ((*tokens)->type == TOKEN_APPEND)
			add_file_node((*files_list),
				create_file_node((*tokens)->next->value, OUTFILE_APPEND));
		else
			cmd[arg_id++] = expand_env_var(tokens, env_list);
		*tokens = (*tokens)->next;
	}
	cmd[arg_id] = NULL;
	cmd_node = create_cmd_node(cmd, *files_list);
	return (cmd_node);
}

void	parse_and_group_commands(t_commands_list **cmd_list,
		t_token_list **token_list, t_env *env_list)
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
			if (current_token->next && current_token->next->type == TOKEN_PIPE)
			{
				printf("Syntax error: consecutive pipes\n");
				return ;
			}
			cmd_node = create_pipe_node();
			add_cmd_node(*cmd_list, cmd_node);
			current_token = current_token->next;
		}
		else
		{
			cmd_node = parse_command(&current_token, &files_list, env_list);
			add_cmd_node(*cmd_list, cmd_node);
		}
	}
}
