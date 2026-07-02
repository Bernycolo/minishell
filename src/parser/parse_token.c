#include "minishell.h"
#include "libft.h"

t_cmd	*parse_token(t_shell *shell)
{
	t_token	*curr;
	int		i;
	int		count;

	init_cmd(&shell->cmd);
	curr = shell->tokens;
	count = 0;
	while (curr)
	{
		if (curr->type == WORD)
			count++;
		curr = curr->next;
	}
	i = 0;
	curr = shell->tokens;
	shell->cmd->arg = malloc(sizeof(char *) * (count + 1));
	while (curr)
	{
		if (curr->type == WORD)
		{
			shell->cmd->arg[i] = ft_strdup(curr->value);
			shell->cmd->argc++;
			i++;
		}
		else
			printf("No Word.\n");
		shell->cmd->arg[i] = NULL;
		curr = curr->next;
	}
	return (shell->cmd);
}
