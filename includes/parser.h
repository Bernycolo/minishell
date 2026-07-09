#ifndef PARSER_H
# define PARSER_H

# include "structs.h"

t_status			parse(const char *input, t_shell *shell);
t_cmd				*parse_token(t_shell *shell);
void				print_syntax_error(t_token *token);
void				print_token_list(t_token *token_list);

#endif