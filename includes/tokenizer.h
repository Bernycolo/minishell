/**
 * @file tokenizer.h
 * @author bconejo-
 * @brief Tokenizer module for minishell
 * @version 0.1
 * @date 2026-06-20
 * 
 * @copyright Copyright (c) 2026
 * 
 */

#ifndef TOKENIZER_H
# define TOKENIZER_H

/**
 * @enum e_status
 * @brief Generic success/failure status used across the project
 * 
 * This enumeration is used as a return value to indicate whether an operation
 * completed successfully or encountered an error
 */
typedef enum e_status
{
	FAILURE,
	SUCCESS
}					t_status;

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
t_token				*tokenizer(const char *input);

t_status			lexer_validate(t_token *token);

#endif
