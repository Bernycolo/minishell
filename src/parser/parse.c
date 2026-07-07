#include "minishell.h"
#include "libft.h"

/*
int	op_count(const char *input)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (input && input[i])
	{
		if (input[i] == '>' && input[i + 1] && input[i + 1] == '>')
		{
			count++;
			i += 2;
		}
		else if (input[i] == '<' && input[i + 1] && input[i + 1] == '<')
		{
			count++;
			i += 2;
		}
		else if (ft_strchr("|<>", input[i]))
			count++;
		i++;
	}
	return (count);
}
*/

/**
 * @brief Prints the content of a tokens list
 * 
 * @param token_list The tokens list to print
 */
void	print_token_list(t_token *token_list)
{
	t_token	*token;
	char	*type_op;

	type_op = NULL;
	token = token_list;
	while (token)
	{
		if (token->type == WORD)
			type_op = ft_strdup("WORD");
		if (token->type == TRUNC)
			type_op = ft_strdup("TRUNC");
		if (token->type == INPUT)
			type_op = ft_strdup("INPUT");
		if (token->type == APPEND)
			type_op = ft_strdup("APPEND");
		if (token->type == HEREDOC)
			type_op = ft_strdup("HEREDOC");
		if (token->type == PIPE)
			type_op = ft_strdup("PIPE");
		printf("value: %s \t type: %s \n", token->value, type_op);
		free (type_op);
		token = token->next;
	}
}

t_status	parse(const char *input, t_shell *shell)
{
	shell->tokens = tokenizer(input);
	if (shell->tokens)
	{
		expand_tokens(&shell->tokens, shell->env, shell->last_status);
		if (lexer_validate(shell->tokens))
		{
			shell->cmd = parse_token(shell);
			if (!shell->cmd)
			{
				printf("Error: syntax error!\n");
				return (FAILURE);	
			}
//			free_tokenlst(&shell->tokens);
			return (SUCCESS);
		}
		else
		{
			printf("Error: syntax error!\n");
			free_tokenlst(&shell->tokens);
			return (FAILURE);
		}
	}
	else
		return (FAILURE);
}
