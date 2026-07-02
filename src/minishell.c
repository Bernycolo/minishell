#include "minishell.h"
#include "libft.h"

void	print_cmd(t_cmd *cmd)
{
	int	i;

	i = 0;
	if (cmd->arg)
	{
		while (cmd->arg[i])
		{
			printf("%s\n", cmd->arg[i]);
			i++;
		}

	}
	return ;
}

int	main(int ac, char **av, char **envp)
{
	char	*str;
	char	*prompt;
	t_shell	shell;

	(void)av;
	if (ac == 1)
	{
		prompt = init_shell(&shell, envp);
		str = readline(prompt);
		while (str != NULL && str[0] != 0)
		{
			if (parse(str, &shell))
			{
				add_history(str);
				print_cmd(shell.cmd);
				free_cmd(&shell.cmd);
			}
			free(str);
			str = readline(prompt);
		}
		free(prompt);
		end_shell(&shell);
		free(str);
		return (0);
	}
	printf("Error!\n");
	return (1);

}
