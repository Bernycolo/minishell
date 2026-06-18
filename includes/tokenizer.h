#ifndef TOKENIZER_H
# define TOKENIZER_H

# include <stdio.h>
# include "libft.h"

typedef enum e_status
{
	FAILURE,
	SUCCESS
}					t_status;

typedef enum e_token_type
{
	WORD,
	TRUNC,
	INPUT,
	APPEND,
	HEREDOC,
	PIPE,
	EMPTY,
	CMD,
	ARG,
	END
}					t_token_type;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	struct s_token	*next;
}					t_token;

t_status			is_op(const char *input, int i);
char				*read_word(const char *input, int *i);
void				create_and_add_token(t_token **list, const char *value,
						t_token_type type);
void				free_tokenlst(t_token **token_lst);
t_token				*tokenizer(const char *input);

#endif
