#include "minishell.h"
#include "libft.h"

int	main(int ac, char **av, char **envp)
{
	char	*str;
	char	*prompt;
	t_shell	shell;

	(void)ac;
	(void)av;
	prompt = init_shell(&shell, envp);
	str = readline(prompt);
	while (str != NULL && str[0] != 0)
	{
		if (parse(str, shell.cmd, shell.env))
			add_history(str);
		free(str);
		str = readline(prompt);
	}
	free(prompt);
	end_shell(&shell);
	free(str);
}
