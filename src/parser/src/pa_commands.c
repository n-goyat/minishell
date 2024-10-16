/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pa_commands.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoyat <ngoyat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 15:40:49 by ngoyat            #+#    #+#             */
/*   Updated: 2024/10/16 16:23:55 by ngoyat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pa_header.h"

t_cmd_node	*create_cmd_node(char **cmd, t_file_node *files)
{
	t_cmd_node	*new_node;

	new_node = malloc(sizeof(t_cmd_node));
	if (!new_node)
		return (NULL);
	new_node->cmd = cmd;     // Command and arguments (e.g., {"ls", "-l", NULL})
	new_node->files = files; // Redirection files
	new_node->next = NULL;
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
}

t_cmd_node	*parse_command(t_token **tokens, t_file_node *files)
{
	t_cmd_node	*cmd_node;
	char		**cmd;
	int			arg_id;

	files = create_file_node();
	cmd = malloc(sizeof(char *) * 10);
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
	t_cmd_node	*cmd_node;

	while (tokens)
	{
		if (tokens->type == TOKEN_APPEND || tokens->type == TOKEN_REDIRECT_IN
			|| tokens->type == TOKEN_REDIRECT_OUT)
		{
			cmd_node = parse_command(&tokens);
			add_cmd_node(cmd_list, cmd_node);
		}
		if (tokens && tokens->type == TOKEN_PIPE)
			tokens = tokens->next;
	}
}
