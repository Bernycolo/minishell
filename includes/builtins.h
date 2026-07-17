#ifndef BUILTINS_H
# define BUILTINS_H

# include "structs.h"

t_status	is_builtin(t_cmd *cmd);
void		ft_builtin(t_shell *shell);

void		builtin_exit(t_shell *shell);

#endif