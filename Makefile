# Variables
CC = cc
CFLAGS = -Wall -Werror -Wextra -I/usr/include
INCLUDES = -I includes -I $(LIBFT_DIR)

SRC_DIR = src
OBJ_DIR = obj

LIBS = -lreadline

NAME = minishell

GREEN = \033[0;32m
RESET = \033[0m

# Files
SRC = 	parser/parse.c parser/parse_token.c parser/parse_token_handlers.c \
		parser/parse_token_utils.c parser/parser_utils.c \
		tokenizer/tokenizer.c tokenizer/tokenizer_utils.c tokenizer/read_word.c \
		expander/expander.c expander/expander_utils.c \
		lexer/lexer.c \
		cmd/cmd.c cmd/cmd_utils.c \
		env/env.c env/env_utils.c \
		utils/utils.c \
		minishell.c
OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)
DEP = $(OBJ:.o=.d)

#Libft
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

# Rules
all: $(NAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(LIBFT):
	@$(MAKE) -s -C $(LIBFT_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -MMD -MP -c $< -o $@

$(NAME): $(LIBFT) $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) $(LIBS) $(LIBFT) -o $(NAME)
	@printf "$(GREEN)✓$(RESET) $(NAME) compiled successfully.\n"

-include $(DEP)

# Other rules
clean:
	@rm -rf $(OBJ_DIR)
	@$(MAKE) -s -C $(LIBFT_DIR) clean
	@printf "$(GREEN)✓$(RESET) Obj files cleaned.\n"

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -s -C $(LIBFT_DIR) fclean
	@printf "$(GREEN)✓$(RESET) All executables removed.\n"

re: fclean all

.PHONY: all clean fclean re
