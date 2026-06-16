#include "minishell.h"

int	main(void)
{
	char	*str;
	char	*prompt;
	t_cmd	*cmd;

	if (!init_cmd(&cmd))
		return (1);
	printf("\033[2J\033[H");
	printf("Welcome to minishell!\n");
	prompt = ft_strjoin(SOFT_YELLOW "minishell" RESET " % ", GRAY);
	str = readline(prompt);
	while (str !=NULL && str[0] != 0)
	{
		if (parse(str, cmd))
		add_history(str);
		free(str);
		ft_printf("%s", prompt);
		str = readline(prompt);
	}
	free(prompt);
	free_cmd(&cmd);
	free(str);
}
