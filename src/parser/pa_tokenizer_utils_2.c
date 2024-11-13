
#include "../includes/pa_header.h"

void	expand_token_value(t_token *token, t_env_list *env_list)
{
	char	*expanded_value;
	int		i;

	i = 0;
	if (token->type == TOKEN_WORD && token->value[0] == '$')
	{
		expanded_value = expand_single_variable(token->value, &i, env_list);
		free(token->value);
		token->value = expanded_value;
	}
}
