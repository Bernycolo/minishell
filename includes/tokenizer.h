#ifndef TOKENIZER_H
# define TOKENIZER_H

# include "structs.h"

/**
 * @enum e_token_type
 * @brief Token types produced by the tokenizer
 * 
 * These values represent the different kinds of lexical elements that can be
 * extracted from the input string before parsing
 * 
 */
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

/**
 * @struct s_token
 * @brief Node of the token list produced by the tokenizer
 * 
 * Each token contains a string value, its type, and a pointer to the next
 * token in the secuence. This structure is used by both the tokenizer and
 * the parser
 */
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
char				*ft_strjoin_free(char *s1, char *s2);
t_token				*tokenizer(const char *input);

t_status			lexer_validate(t_token *token);

#endif
