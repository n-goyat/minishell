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
	t_cmd_node	*cmd_node;
	char		**cmd;
	int			arg_id;

	cmd = NULL;
	(void)env_list;
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
	cmd_node = create_cmd_node(cmd, *files_list);
	return (cmd_node);
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
