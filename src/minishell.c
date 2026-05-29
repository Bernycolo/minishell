#include "minishell.h"

int	main(void)
{
	char	*str;
	char	*prompt;
	t_cmd	*cmd;
	int	i;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (1);
	printf("\033[2J\033[H");
	printf("Welcome to minishell!\n");
	prompt = ft_strjoin(SOFT_YELLOW "minishell" RESET " % ", GRAY);;
	str = readline(prompt);
	while (str[0] != 0)
	{
		if (parse(str, cmd))
		{
			add_history(str);
			i = 0;
			while (cmd->arg[i])
				printf("DEBUG: %s\n", cmd->arg[i++]);
			
		}
		free(str);
		str = readline(prompt);
	}
	free(prompt);
	free(cmd);
	free(str);
}
