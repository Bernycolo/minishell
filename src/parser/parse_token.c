#include "minishell.h"
#include "libft.h"

int	count_arg(char **arg)
{
	int	i;

	i = 0;
	while (arg && arg[i])
		i++;
	return (i);
}

char	**add_arg(t_cmd *cmd, char *value)
{
	int		n_args;
	int		i;
	char	**new_arg;

	n_args = count_arg(cmd->arg);
	new_arg = malloc(sizeof(char *) * (n_args + 2));
	i = 0;
	if (cmd->arg)
	{
		while (cmd->arg[i])
		{
			new_arg[i] = ft_strdup(cmd->arg[i]);
			i++;
		}
	}
	new_arg[i] = ft_strdup(value);
	new_arg[i + 1] = NULL;
	i = 0;
	while (cmd->arg && cmd->arg[i])
		free(cmd->arg[i++]);
	if (cmd->arg)
		free(cmd->arg);
	return (new_arg);
}

t_status	manage_start(t_token *tokens, t_cmd **cmds, t_pstate *state)
{
	if (tokens->type == WORD)
	{
		(*cmds)->arg = add_arg(*cmds, tokens->value);
		(*cmds)->argc++;
		*state = PS_WORD;
		return (SUCCESS);
	}
	else if (tokens->type == TRUNC || tokens->type == INPUT
		|| tokens->type == APPEND || tokens->type == HEREDOC)
	{
		add_redir(*cmds, tokens->type);
		*state = PS_REDIR;
		return (SUCCESS);
	}
	print_syntax_error(tokens);
	return (FAILURE);
}

t_status	manage_word(t_token *tokens, t_cmd **cmds, t_pstate *state)
{
	t_cmd	*new;

	if (tokens->type == WORD)
	{
		(*cmds)->arg = add_arg(*cmds, tokens->value);
		(*cmds)->argc++;
	}
	else if (tokens->type == TRUNC || tokens->type == INPUT
		|| tokens->type == APPEND || tokens->type == HEREDOC )
		{
			add_redir(*cmds, tokens->type);
			*state = PS_REDIR;
		}
	else if (tokens->type == PIPE)
	{
		new_cmd(&new);
		(*cmds)->next = new;
		*cmds = new;
		*state = PS_PIPE;
	}
	else
	{
		print_syntax_error(tokens);
		return (FAILURE);
	}
	return (SUCCESS);
}

t_status	is_quoted(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
			return (SUCCESS);
		i++;
	}
	return (FAILURE);
}

/*

char    *remove_quotes(char *str)
{
	int     i;
	int     j;
	char    quote;
	char    *result;
	int     len;

	if (!str)
		return (NULL);
	len = ft_strlen(str);
	result = malloc(len + 1);
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			quote = str[i++];        // abrir quoting
			while (str[i] && str[i] != quote)
				result[j++] = str[i++];  // copiar contenido interno
			if (str[i] == quote)
				i++;                    // cerrar quoting
		}
		else
			result[j++] = str[i++];
	}
	result[j] = '\0';
	return (result);
}
*/


char	*remove_quotes(char *str)
{
    char	*result;
    int		i;
    int		j;
    char	quote;

    result = malloc(ft_strlen(str) + 1);
    if (!result)
        return (NULL);
    i = 0;
    j = 0;
    quote = 0;
    while (str && str[i])
    {
        if (!quote && (str[i] == '\'' || str[i] == '"'))
            quote = str[i++];
        else if (quote && str[i] == quote)
        {
            quote = 0;
            i++;
        }
	else
        	result[j++] = str[i++];
    }
    result[j] = '\0';
    return (result);
}





/*
char	*remove_quotes(char *str)
{
	char	*result;
	char	quote;
	int		i;
	int		j;
	
	if (is_quoted(str))
	{
		i = 0;
		j = 0;
		result = malloc(ft_strlen(str));
		while (str[i])
		{
			while (str[i] != '"' && str[i] != '\'')
				result[j++] = str[i++];
			quote = str[i++];
			while (str[i] && str[i] != quote)
				result[j++] = str[i++];
			i++;
//			while (str[i])
//				result[j++] = str[i++];
		}
		result[j] = '\0';
		return (result);
	}
	else
		return (ft_strdup(str));
}

*/



t_status	manage_redir(t_token *tokens, t_cmd **cmds, t_pstate *state)
{
	t_redir	*last;

	if (tokens->type == WORD)
	{
		last = (*cmds)->redirs;
		if (!last)
			return (FAILURE);
		while (last && last->next)
			last = last->next;
		if (last->type != HEREDOC)
			last->target = ft_strdup(tokens->value);
		else
		{
			last->quoted = is_quoted(tokens->value);
			last->target = remove_quotes(tokens->value);
		}
		*state = PS_AFTER_REDIR;
		return (SUCCESS);
	}
	print_syntax_error(tokens);
	return (FAILURE);
}

t_status	manage_after_redir(t_token *tokens, t_cmd **cmds, t_pstate *state)
{
	if (tokens->type == TRUNC || tokens->type == INPUT
		|| tokens->type == APPEND || tokens->type == HEREDOC)
	{
		add_redir(*cmds, tokens->type);
		*state = PS_REDIR;
	}
	else if (tokens->type == PIPE)
		*state = PS_PIPE;
	else if (tokens->type == WORD)
	{
		(*cmds)->arg = add_arg(*cmds, tokens->value);
		(*cmds)->argc++;
		*state = PS_WORD;
	}
	else
	{
		print_syntax_error(tokens);
		return (FAILURE);
	}
	return (SUCCESS);
}

t_status	manage_pipe(t_token *tokens, t_cmd **cmds, t_pstate *state)
{
	t_cmd	*new;

	if (tokens->type == WORD)
	{
		new_cmd(&new);
		(*cmds)->next = new;
		*cmds = new;
		new->arg = add_arg(new, tokens->value);
		new->argc = 1;
		*state = PS_WORD;
		return (SUCCESS);
	}
		if (tokens->type == TRUNC || tokens->type == INPUT
		|| tokens->type == APPEND || tokens->type == HEREDOC)
	{
		new_cmd(&new);
		(*cmds)->next = new;
		*cmds = new;
		add_redir(new, tokens->type);
		*state = PS_REDIR;
		return (SUCCESS);
	}
	print_syntax_error(tokens);
	return (FAILURE);
}

t_status	fill_cmd(t_shell **shell)
{
	t_pstate	state;
	t_status	result_state;
	t_token		*tokens;
	t_cmd		*cmds;

	tokens = (*shell)->tokens;
	cmds = (*shell)->cmd;
	state = PS_START;
	result_state = SUCCESS;
	while (tokens && result_state)
	{
		if (state == PS_START)
			result_state = manage_start(tokens, &cmds, &state);
		else if (state == PS_WORD)
			result_state = manage_word(tokens, &cmds, &state);
		else if (state == PS_REDIR)
			result_state = manage_redir(tokens, &cmds, &state);
		else if (state == PS_AFTER_REDIR)
			result_state = manage_after_redir(tokens, &cmds, &state);
		else
			result_state = manage_pipe(tokens, &cmds, &state);
		tokens = tokens->next;
	}
	return (result_state);
}

t_cmd	*parse_token(t_shell *shell)
{
	new_cmd(&shell->cmd);
	if (!fill_cmd(&shell))
	{
		free_tokenlst(&shell->tokens);
		free_cmd(&shell->cmd);
		return (NULL);
	}
	free_tokenlst(&shell->tokens);
	return (shell->cmd);
}
