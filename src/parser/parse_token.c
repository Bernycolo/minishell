#include "minishell.h"
#include "parse_token.h"

/**
 * @brief Completes a command list
 * 
 * @param shell The golbal status of minishell
 * @return SUCCESS if its completed, FAILURE otherwise 
 */
static t_status	fill_cmd(t_shell **shell)
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

/**
 * @brief Parses a token list
 * 
 * @param shell The global status of minishell
 * @return The command parsed 
 */
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
