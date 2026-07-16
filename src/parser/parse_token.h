#ifndef PARSE_TOKEN_H
# define PARSE_TOKEN_H

# include "structs.h"

t_status	manage_start(t_token *tokens, t_cmd **cmds, t_pstate *state);
t_status	manage_word(t_token *tokens, t_cmd **cmds, t_pstate *state);
t_status	manage_redir(t_token *tokens, t_cmd **cmds, t_pstate *state);
t_status	manage_after_redir(t_token *tokens, t_cmd **cmds, t_pstate *state);
t_status	manage_pipe(t_token *tokens, t_cmd **cmds, t_pstate *state);
char		**add_arg(t_cmd *cmd, char *value);
t_status	is_redir_token(t_token_type type);
t_status	is_quoted(char *str);
char		*remove_quotes(char *str);

#endif