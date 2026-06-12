#include "minishell.h"

t_token	*new_token(char *value, t_token_type token_type)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->value = value;
	token->type = token_type;
	token->next = NULL;
	return (token);
}

void	add_token(t_token **list, t_token *new)
{
	t_token	*aux;

	if (!list)
		return ;
	if (*list)
	{
		aux = *list;
		while (aux->next != NULL)
			aux = aux->next;
		aux->next = new;
	}
	else if (new)
		*list = new;
}

void	create_and_add_token(t_token **list, const char *value, t_token_type type)
{
	t_token	*token;
	char	*token_value;

	token = NULL;
	token_value = NULL;
	if (type == HEREDOC || type == APPEND)
	{
		token_value = malloc(3);
		if (!token_value)
			return ;
		ft_strlcpy(token_value, value, 3);
		token = new_token(token_value, type);
		if (!token)
		{
			free (token_value);
			return ;
		}
	}
	else if (type == PIPE || type == TRUNC || type == INPUT)
	{
		token_value = malloc(2);
		if (!token)
			return ;
		ft_strlcpy(token_value, value, 2);
		token = new_token(token_value, type);
		if (!token)
		{
			free (token_value);
			return ;
		}
	}
	else if (type == WORD)
	{
		token = new_token(ft_strdup(value), WORD);
		if (!token)
			return ;
	}
	add_token(list, token);
}

void	skip_spaces(const char *input, int *i)
{
	while (input && input[*i] == ' ')
		*i += 1;
}

t_status	is_op(const char *input, int i)
{
	if (ft_strchr("<>|", input[i]))
		return (SUCCESS);
	return (FAILURE);
}

t_token_type	type_op(const char *input, int *i)
{
	if (input[*i] == '<' && input[*i + 1] && input[*i + 1] == '<')
	{
		*i += 2;
		return (HEREDOC);
	}
	else if (input[*i] == '>' && input[*i + 1] && input[*i + 1] == '>')
	{
		*i += 2;
		return (APPEND);
	}
	else if (input[*i] == '|')
	{
		*i += 1;
		return (PIPE);
	}
	else if (input[*i] == '<')
	{
		*i += 1;
		return (INPUT);
	}
	else
	{
		*i += 1;
		return (TRUNC);
	}
}

char	*value_op(t_token_type type)
{
	if (type == HEREDOC)
		return ("<<");
	if (type == APPEND)
		return (">>");
	if (type == INPUT)
		return ("<");
	if (type == TRUNC)
		return (">");
	return ("|");
}

t_token	*tokenizer(const char *input)
{
	t_token			*list;
	t_token_type	type;
	int				i;
	int				start;
	int				len_token;
	char	*word;

	ft_printf("Entra en tokenizer\n");
	list = NULL;
	i = 0;
	while (input && input[i])
	{
		skip_spaces(input, &i);
		if (is_op(input, i))
		{
			type = type_op(input, &i);
			create_and_add_token(&list, value_op(type), type);
		}
		else
		{
			start = i;
			while (input[i] && input[i] != ' ' && !is_op(input, i))
				i++;
			len_token = i  - start;
			word = ft_substr(input, start, len_token);
			if (word)
			{
				create_and_add_token(&list, input, WORD); // crear y añadir token
				free (word);
			}
		}
	}
	return (list);
}
/*
t_token	*tokenizer(char *input)
{
	t_token	*tokens;
	t_token	*token;
	int		i;

	tokens = NULL;
	i = 0;
	while (input && input[i] == ' ')
		i++;
	while (input && input[i])
	{
		if (input[i] == '<' && input[i + 1] && input[i + 1] == '<')
		{
			token = new_token(ft_strdup("<<"), HEREDOC);
			add_token(&tokens, token);
			token = NULL;
			i++;
		} else if (input[i] == '>' && input[i + 1] && input[i + 1] == '>')
		{
			token = new_token(ft_strdup(">>"), APPEND);
			add_token(&tokens, token);
			token = NULL;
			i++;
		} else if (input[i] == '<')
		{
			token = new_token(ft_strdup("<"), INPUT);
			add_token(&tokens, token);
			token = NULL;
		} else if (input[i] == '>')
		{
			token = new_token(ft_strdup(">"), TRUNC);
			add_token(&tokens, token);
			token = NULL;
		} else if (input[i] == '|')
		{
			token = new_token(ft_strdup("|"), PIPE);
			add_token(&tokens, token);
			token = NULL;
		}
		i++;
	}
	return (tokens);
}
*/