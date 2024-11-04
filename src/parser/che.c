#include "includes/pa_header.h"

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
				printf("syntax error near unexpected token `|'\n");
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


// Search for an environment variable by name in the environment list
char	*get_env_value(char *env_name, t_env *env_list)
{
	t_env	*current;

	current = env_list;
	while (current)
	{
		if (ft_strcmp(current->key, env_name) == 0)
			return (ft_strdup(current->value));
		current = current->next;
	}
	return (NULL);
}

// Utility function to concatenate two strings and free the first one
char	*ft_strjoin_free(char *s1, const char *s2)
{
	char	*result;
	size_t	len1;
	size_t	len2;

	if (!s1 || !s2)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	result = malloc(len1 + len2 + 1);
	if (!result)
	{
		free(s1);
		return (NULL);
	}
	ft_memcpy(result, s1, len1);
	ft_memcpy(result + len1, s2, len2 + 1);
	free(s1);
	return (result);
}

// Extract the variable name after a '$' in the token
char	*extract_env_name(const char *str, int *i)
{
	int		start;
	int		length;
	char	*env_name;

	start = *i + 1;
	length = 0;
	while (str[start + length] && (isalnum(str[start + length]) || str[start
			+ length] == '_'))
		length++;
	env_name = ft_substr(str, start, length);
	*i = start + length;
	return (env_name);
}

// Expand a single '$' variable occurrence
char	*expand_single_variable(const char *str, int *i, t_env *env_list)
{
	char	*env_name;
	char	*expanded_value;

	env_name = extract_env_name(str, i);
	expanded_value = get_env_value(env_name, env_list);
	if (!expanded_value)
		expanded_value = ft_strjoin("$", env_name);
	free(env_name);
	return (expanded_value);
}

// Main function to expand all environment variables in the token's value
char	*expand_env_var(t_token **token, t_env *env_list)
{
	char	*result;
	char	tmp[2];
	int		i;
	char	*expanded;

	if ((*token)->type == TOKEN_SIN_QOTES)
		return (ft_strdup((*token)->value));
	result = ft_strdup("");
	i = 0;
	while ((*token)->value[i] != '\0')
	{
		if ((*token)->value[i] == '$')
		{
			expanded = expand_single_variable((*token)->value, &i, env_list);
			result = ft_strjoin_free(result, expanded);
			free(expanded);
		}
		else
		{
			tmp[0] = (*token)->value[i];
			tmp[1] = '\0';
			result = ft_strjoin_free(result, tmp);
			i++;
		}
	}
	return (result);
}


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

void	print_cmd_list(t_commands_list *cmd_list)
{
	t_cmd_node	*current_cmd;
	t_file_node	*current_file;
	int			i;

	current_cmd = cmd_list->head;
	while (current_cmd)
	{
		printf("\nCommand:\n");
		for (i = 0; current_cmd->cmd[i]; i++)
			printf("Arg[%d]: %s\n", i, current_cmd->cmd[i]);
		if (current_cmd->files && current_cmd->files->head)
		{
			printf("Files:\n");
			current_file = current_cmd->files->head;
			while (current_file)
			{
				printf("File: %s, Type: %d\n", current_file->filename,
					current_file->type);
				current_file = current_file->next;
			}
		}
		current_cmd = current_cmd->next;
	}
}

// Function to create a new token
t_token *create_token(char *value, int type)
{
        t_token *new_token;

        (void)value;
        (void)type;
        new_token = malloc(sizeof(t_token));
        if (!new_token)
                return (NULL);
        new_token->value = NULL;
        new_token->type = 0;
        new_token->next = NULL;
        return (new_token);
}

// Function to add a token to the list
void    add_token(t_token_list *token_list, t_token *new_token)
{
        if (!new_token)
                return ;
        if (!token_list->head)
        {
                token_list->head = new_token;
                token_list->tail = new_token;
        }
        else
        {
                token_list->tail->next = new_token;
                token_list->tail = new_token;
        }
        token_list->size++;
}

t_token_list    *init_token_list(void)
{
        t_token_list    *token_list;

        token_list = malloc(sizeof(t_token_list));
        if (!token_list)
                return (NULL);
        token_list->head = NULL;
        token_list->tail = NULL;
        token_list->size = 0;
        return (token_list);
}
// Function to determine the token type
int     determine_type(char *token)
{
        if (strcmp(token, "|") == 0)
                return (TOKEN_PIPE);
        if (strcmp(token, "<") == 0)
                return (TOKEN_REDIRECT_IN);
        if (strcmp(token, ">") == 0)
                return (TOKEN_REDIRECT_OUT);
        if (strcmp(token, ">>") == 0)
                return (TOKEN_APPEND);
        if (strcmp(token, "\'") == 0)
                return (TOKEN_SIN_QOTES);
        if (strcmp(token, "\"") == 0)
                return (TOKEN_DBL_QOTES);
        return (TOKEN_WORD);
}

// Function to print tokens (for testing)
void    print_tokens(t_token_list *token_list)
{
        t_token *current_token;

        if (!token_list || !token_list->head)
        {
                printf("Token list is empty.\n");
                return ;
        }
        current_token = token_list->head;
        while (current_token != NULL)
        {
                printf("Token: %s, Type: %d\n", current_token->value,
                        current_token->type);
                current_token = current_token->next;
        }
}

int     ft_word_len(char *word)
{
        int     i;

        i = 0;
        while (word[i] != ' ' && word[i] != '\0')
                i++;
        return (i);
}

int     write_token(char *in, int *i, t_token *token, t_token_type typ)
{
        int     token_length;

        token->type = typ;
        if (typ == TOKEN_REDIRECT_IN || typ == TOKEN_REDIRECT_OUT)
                token_length = 1;
        else if (typ == TOKEN_APPEND || typ == TOKEN_HEREDOC)
                token_length = 2;
        else if (typ == TOKEN_PIPE)
                token_length = 1;
        else if (typ == TOKEN_DBL_QOTES || typ == TOKEN_SIN_QOTES)
        {
                token_length = handle_quotes(in + *i, token, typ);
                if (token_length == -1)
                {
                        printf("Syntax error: Unclosed quotes\n");
                        return (-1);
                }
        }
        else
                token_length = ft_word_len(in + *i);
        if (typ != TOKEN_DBL_QOTES && typ != TOKEN_SIN_QOTES)
                token->value = ft_strndup(in + *i, token_length);
        *i += token_length;
        return (0);
}

int     handle_quotes(char *in, t_token *token, t_token_type typ)
{
        int             i;
        char    quote_char;

        if (typ == TOKEN_DBL_QOTES)
                quote_char = '\"';
        else if (typ == TOKEN_SIN_QOTES)
                quote_char = '\'';
        else
                return (-1);
        i = 1;
        while (in[i] != quote_char)
        {
                if (in[i] == '\0')
                        return (-1);
                i++;
        }
        token->value = ft_strndup(in + 1, i - 1);
        return (i + 1);
}

int     assign_token_typ(char *in, int *i, t_token *token)
{
        if (strncmp(in + *i, "<<", 2) == 0)
                return (write_token(in, i, token, TOKEN_HEREDOC));
        else if (strncmp(in + *i, ">>", 2) == 0)
                return (write_token(in, i, token, TOKEN_APPEND));
        else if (strncmp(in + *i, "<", 1) == 0)
                return (write_token(in, i, token, TOKEN_REDIRECT_IN));
        else if (strncmp(in + *i, ">", 1) == 0)
                return (write_token(in, i, token, TOKEN_REDIRECT_OUT));
        else if (strncmp(in + *i, "|", 1) == 0)
                return (write_token(in, i, token, TOKEN_PIPE));
        else if (strncmp(in + *i, "\"", 1) == 0)
                return (write_token(in, i, token, TOKEN_DBL_QOTES));
        else if (strncmp(in + *i, "\'", 1) == 0)
                return (write_token(in, i, token, TOKEN_SIN_QOTES));
        else
                return (write_token(in, i, token, TOKEN_WORD));
}

t_token_list    *tokenize_input(char *in)
{
        t_token_list    *token_list;
        t_token                 *new_token;
        int                             i;

        i = 0;
        token_list = init_token_list();
        if (!token_list)
                return (NULL);
        while (in[i])
        {
                if (in[i] == ' ')
                {
                        i++;
                        continue ;
                }
                new_token = create_token(NULL, 0);
                if (assign_token_typ(in, &i, new_token) == -1)
                        return (NULL);
                add_token(token_list, new_token);
        }
        return (token_list);
}
