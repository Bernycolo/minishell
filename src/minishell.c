#include "minishell.h"
#include "libft.h"

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
		while (1)
		{
			if (parse(str, &shell))
			{
				add_history(str);
				executor(&shell);
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
