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

void	create_and_add_token(t_token **list, char *value)
{
	t_token	*token;

	token = new_token(ft_strdup(value), type);
	if (!token)
		return ;
	add_token(list, token);
}

void	skip_spaces(char *input, int *i)
{
	while (input && input[*i] == ' ')
		*i++;
}

t_status	is_heredoc(char *input, int *i)
{
	if (input[*i] == '<' && input[*i + 1] && input[*i + 1] == '<')
		return (SUCCESS);
	return (FAILURE);
}

t_status	is_append(char *input, int *i)
{
	if (input[*i] == '>' && input[*i + 1] && input[*i + 1] == '>')
		return (SUCCESS);
	return (FAILURE);
}

t_status	ip_op(char *input, int *i)
{
	if (ft_strchr("|<>", input[*i]))
		return (SUCCESS);
	return (FAILURE);
}

t_token	**tokenizer(char *input)
{
	t_token	*list;
	int	i;

	list = NULL;
	i = 0;
	while (input && input[i])
	{
		skip_spaces(input, &i);
		if (is_heredoc(input, &i) || is_append(input, &i))
		{
			// crear y añadir token
			i += 2;
		} else if (is_op(input, &i))
		{
			// crear y añadir token
			create_and_add_token(list, input[i]);
			i++;
		} else
		{
			i++;
		}
	}
}

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
