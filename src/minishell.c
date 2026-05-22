#include "minishell.h"

int	main(void)
{
	char	*str;
	char	*prompt;

	printf("\033[2J\033[H");
	printf("Welcome to minishell!\n");
	prompt = ft_strjoin(SOFT_YELLOW "minishell" RESET " % ", GRAY);;
	str = readline(prompt);
	while (str[0] != 0)
	{
		add_history(str);
		printf("DEBUG: %s\n", str);
		free(str);
		str = readline(prompt);
	}
	free(str);
}
