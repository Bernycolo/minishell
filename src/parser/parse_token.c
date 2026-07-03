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


char	**add_arg(t_cmd	*cmd, char *value)
{
	int		n_args;
	int		i;
	char	**new_arg;

	n_args = count_arg(cmd->arg);
	new_arg = malloc(sizeof(char *) * (n_args + 2));
	i = 0;
	while (cmd->arg[i])
	{
		new_arg[i] = ft_strdup(cmd->arg[i]);
		i++;
	}
	new_arg[i] = ft_strdup(value);
	new_arg[i + 1] = NULL;

	i = 0;
	while (i < n_args)
	{
		printf("%s\n", new_arg[i]);
		i++;
	}


	free(cmd->arg);
	return (new_arg);
}

int	count_words(t_token *tokens)
{
	int		count;
	t_token	*curr;

	count = 0;
	curr = tokens;
	while (curr)
	{
		if (curr->type == WORD)
			count++;
		else if (curr->type == PIPE)
			break;
		curr = curr->next;
	}
	return (count);
}

t_status	fill_cmd(t_shell **shell)
{
	int		i;
	t_token	*curr;

	i = count_words((*shell)->tokens);
	if (i <= 0)
		return (FAILURE);
	curr = (*shell)->tokens;
	(*shell)->cmd->arg = malloc(sizeof(char *) * (i + 1));
	if (!(*shell)->cmd->arg)
		return (FAILURE);
	while (curr)
	{
		if (curr->type == WORD)
		{
			(*shell)->cmd->arg = add_arg((*shell)->cmd, curr->value);
			(*shell)->cmd->argc++;
		}
		else
			printf("No Word.\n");
		curr = curr->next;
	}
	return (SUCCESS);
}

t_cmd	*parse_token(t_shell *shell)
{
	init_cmd(&shell->cmd);
	if (!fill_cmd(&shell))
		return (NULL);
	return (shell->cmd);
}
