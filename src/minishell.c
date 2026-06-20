#include "minishell.h"
#include "libft.h"

int	main(int ac, char **av, char **envp)
{
	char	*str;
	char	*prompt;
	t_cmd	*cmd;
	t_env	*env;

	(void)ac;
	(void)av;
	env = NULL;
	if (!init_cmd(&cmd))
		return (1);
	printf("\033[2J\033[H");
	env_init(&env, envp);
	printf("Welcome to minishell!\n");
	prompt = ft_strjoin(SOFT_YELLOW "minishell" RESET " % ", GRAY);
	str = readline(prompt);
	while (str != NULL && str[0] != 0)
	{
		if (parse(str, cmd))
			add_history(str);
		free(str);
		str = readline(prompt);
	}
	free(prompt);
	free_env(&env);
	free_cmd(&cmd);
	free(str);
}
