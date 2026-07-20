#include "minishell.h"
#include "builtins_utils.h"
/*
static void		ft_export_without_arg(t_shell *msh);
static t_env	*sort_list(t_env *lst);
static t_env	*copy_list(t_env *lst);
static int		check_export(char *arg);
*/

void	builtin_export(t_shell *shell)
{
	//	int	i;
	shell->last_status = 0;
	if (shell->cmd->argc == 1)
		export_no_args(shell);
	else
		print_cmd(shell->cmd);
}

/*
{
i = 0;
while (msh->cmd->arg[++i])
{
if (check_export(msh->cmd->arg[i]))
add_arg_to_env(msh->cmd->arg[i], msh);
else
msh->last_status = 1;
}
}
}
*/
/*
static void	ft_export_without_arg(t_shell *msh)
{
t_env	*tmp;
t_env	*lst_cpy;

lst_cpy = copy_list(msh->env);
tmp = sort_list(lst_cpy);
while (tmp)
{
if (!ft_strncmp(tmp->key, "_\0", 2))
printf(" \r");
else if (tmp->value[0])
printf("declare -x %s=\"%s\"\n", tmp->key, tmp->value);
else
printf("declare -x %s\n", tmp->key);
tmp = tmp->next;
}
free_env(&lst_cpy);
}

static t_env	*sort_list(t_env *lst)
{
t_env	*tmp;
t_env	*swap;

tmp = lst;
swap = new_env("", "");
while (lst->next != NULL)
{
if (lst->next && ft_strcmp(lst->key, lst->next->key) > 0)
{
swap->key = lst->key;
swap->value = lst->value;
lst->key = lst->next->key;
lst->value = lst->next->value;
lst->next->key = swap->key;
lst->next->value = swap->value;
lst = tmp;
}
else
lst = lst->next;
}
lst = tmp;
free_mem(swap);
return (lst);
}

static t_env	*copy_list(t_env *lst)
{
t_env	*cpy;
t_env	*tmp;

tmp = lst;
cpy = NULL;
while (tmp)
{
if (!cpy)
cpy = new_env(tmp->key, tmp->value);
else
add_env(&cpy, new_env(tmp->key, tmp->value));
tmp = tmp->next;
}
return (cpy);
}

*/
/*
static int	check_export(char *arg)
{
int		i;
char	*name;

i = 0;
name = get_env_name(arg);
if (ft_isdigit(name[i]))
{
ft_printf("export: %s: not a valid identifier\n", arg);
return (ft_memfree(name), 0);
}
while (name[i])
{
if (ft_isalnum(name[i]) || name[i] == '_')
i++;
else
{
ft_printf("export: %s: not a valid identifier\n", arg);
return (ft_memfree(name), 0);
}
}
return (ft_memfree(name), 1);
}
*/
