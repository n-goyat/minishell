/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pa_commands.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoyat <ngoyat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 15:40:49 by ngoyat            #+#    #+#             */
/*   Updated: 2024/10/16 20:13:07 by ngoyat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pa_header.h"

t_cmd_node	*create_cmd_node(char **cmd, t_file_node *files)
{
	t_cmd_node	*new_node;

	new_node = malloc(sizeof(t_cmd_node));
	if (!new_node)
		return (NULL);
	new_node->cmd = cmd;
	new_node->files = files;
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

t_file_node	*create_file_node(void)
{
	t_file_node	*new_node;

	new_node = malloc(sizeof(t_file_node));
	if (!new_node)
		return (NULL);
	new_node->input_file = NULL;
	new_node->output_file = NULL;
	new_node->append = 0;
	new_node->heredoc = NULL;
	return (new_node);
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

t_cmd_node	*parse_command(t_token **tokens, t_file_node *files)
{
	t_cmd_node	*cmd_node;
	char		**cmd;
	int			arg_id;

	files = create_file_node();
	cmd = malloc(sizeof(char *) * 10); // adapt size
	arg_id = 0;
	while (*tokens && (*tokens)->type != TOKEN_PIPE)
	{
		if ((*tokens)->type == TOKEN_REDIRECT_IN)
			files->input_file = ft_strdup((*tokens)->next->value);
		else if ((*tokens)->type == TOKEN_REDIRECT_OUT)
			files->output_file = ft_strdup((*tokens)->next->value);
		else if ((*tokens)->type == TOKEN_APPEND)
		{
			files->output_file = ft_strdup((*tokens)->next->value);
			files->append = 1;
		}
		else
			cmd[arg_id++] = ft_strdup((*tokens)->value);
		*tokens = (*tokens)->next;
	}
	cmd[arg_id] = NULL;
	cmd_node = create_cmd_node(cmd, files);
	return (cmd_node);
}

void	parse_and_group_commands(t_commands_list *cmd_list, t_token *tokens)
{
	t_file_node	*files;
	t_cmd_node	*cmd_node;

	files = NULL;
	while (tokens)
	{
		if (tokens->type == TOKEN_PIPE)
		{
			if (tokens->next && tokens->next->type == TOKEN_PIPE)
			{
				printf("Syntax error: consecutive pipes\n");
				return ;
			}
			cmd_node = create_pipe_node();
			add_cmd_node(cmd_list, cmd_node);
			tokens = tokens->next;
		}
		else
		{
			cmd_node = parse_command(&tokens, files);
			add_cmd_node(cmd_list, cmd_node);
		}
	}
}
