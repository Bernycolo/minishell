#include "minishell.h"
#include "libft.h"

/**
 * @brief Prints the contents of the tokens list
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
		free(type_op);
		token = token->next;
	}
}

/**
 * @brief Parses an input into a command list
 * 
 * @param input The input to parse
 * @param shell The global status of minishell
 * @return SUCCESS if it is parsed, FAILURE otherwise
 */
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
				return (FAILURE);
			return (SUCCESS);
		}
		else
		{
			free_tokenlst(&shell->tokens);
			return (FAILURE);
		}
	}
	else
		return (FAILURE);
}
