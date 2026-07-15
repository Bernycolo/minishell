#include "minishell.h"
#include "libft.h"

/**
 * @brief Counts the number of argument from an argument's list
 *
 * @param arg The argument's list
 * @return The number of arguments
 */
static int	count_arg(char **arg)
{
	int	i;

	i = 0;
	while (arg && arg[i])
		i++;
	return (i);
}

/**
 * @brief Adds an argument to an argument's list
 *
 * @param cmd The command of the argument's list
 * @param value The argument to add
 * @return The argument's list with the argument added
 */
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

/**
 * @brief Checks if it is a redirect token
 * 
 * @param type The token's type
 * @return SUCCESS if it is a redirect token, FAILURE otherwise
 */
t_status	is_redir_token(t_token_type type)
{
	if (type == TRUNC || type == INPUT || type == APPEND || type == HEREDOC)
		return (SUCCESS);
	return (FAILURE);
}

/**
 * @brief Checks if it is a quoted string
 * 
 * @param str The string to check
 * @return SUCCESS if it is quoted, FAILURE otherwise
 */
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

/**
 * @brief Removes quotes from a string
 * 
 * @param str The string to process
 * @return The string without quotes
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
