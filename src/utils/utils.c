#include "minishell.h"

void	free_tokenlst(t_token **token_lst)
{
	t_token	*aux;

	if (!token_lst || !*token_lst)
		return ;
	aux = *token_lst;
	while (aux->next)
	{
		*token_lst = aux->next;
		free(aux->value);
		free(aux);
		aux = *token_lst;
	}
	free(aux->value);
	free(*token_lst);
	*token_lst = NULL;
}

void	free_cmd(t_cmd **cmd)
{
	t_cmd	*cur;
	t_cmd	*next;
	int	i;

	if (!cmd || !*cmd)
		return ;
	cur = *cmd;
	while (cur)
	{
		next = cur->next;
		if (cur->arg)
		{
			i = 0;
			while (cur->arg[i])
				free(cur->arg[i++]);
			free(cur->arg);
		}
		free(cur->infile);
		free(cur->outfile);
		free(cur);
		cur = next;
	}
	*cmd = NULL;
}
