#include "minishell.h"

int	main(void)
{
	char	*str;
	char	*prompt;
	t_cmd	*cmd;

	cmd = NULL;
	printf("\033[2J\033[H");
	printf("Welcome to minishell!\n");
	prompt = ft_strjoin(SOFT_YELLOW "minishell" RESET " % ", GRAY);;
	str = readline(prompt);
	while (str[0] != 0)
	{
		if (parse(str, cmd))
		{
			add_history(str);
			printf("DEBUG: %s\n", cmd->arg[0]);
			
		}
		free(str);
		str = readline(prompt);
	}
	free(str);
}
