#ifndef EXPANDER_H
# define EXPANDER_H

# include "structs.h"

char	*expand_word(char *value, t_env *env, int last_status);
void	expand_tokens(t_token **list, t_env *env, int last_status);

#endif