#include "minishell.h"

int	main(int ac, char **av, char **envp)
{
	char	*str;
	char	*prompt;
	t_cmd	*cmd;
	t_env	*env;
	t_env	*env_tmp;

	(void)ac;
	(void)av;
	(void)envp;
	env = NULL;
	if (!init_cmd(&cmd))
		return (1);
	printf("\033[2J\033[H");
	env_init(&env, envp);
	printf("Welcome to minishell!\n");
	prompt = ft_strjoin(SOFT_YELLOW "minishell" RESET " % ", GRAY);
	env_tmp = env;
	while (env_tmp)
	{
		printf("%s \t\t %s\n", env_tmp->key, env_tmp->value);
		env_tmp = env_tmp->next;
	}
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
