# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bconejo- <bconejo-@student.42malaga.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/09/04 18:55:59 by bconejo-          #+#    #+#              #
#    Updated: 2026/09/04 20:33:42 by bconejo-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Variables
CC = cc
CFLAGS = -Wall -Werror -Wextra -I/usr/include -g
INCLUDES = -I includes -I $(LIBFT_DIR)

SRC_DIR = src
OBJ_DIR = obj

LIBS = -lreadline -lncurses

NAME = minishell

BLUE = \033[0;34m
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
		builtins/builtcheck.c builtins/builtin_exit.c builtins/builtin_env.c \
		builtins/builtin_echo.c builtins/builtin_pwd.c builtins/builtin_export.c \
		builtins/builtin_export_no_args.c builtins/builtin_export_with_args.c \
		builtins/builtin_cd.c builtins/builtin_unset.c \
		executor/exec.c executor/pipeline_utils.c executor/pipeline_utils_2.c \
		executor/single_exec.c executor/redir.c executor/redir_utils.c \
		signals/signals.c \
		shell/shell.c \
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

# Memory testing rules
valgrind: $(NAME)
	@printf "$(GREEN)Running $(NAME) with Valgrind...$(RESET)\n"
	@valgrind --leak-check=full --show-leak-kinds=all --suppressions=supp.supp --track-origins=yes --track-fds=yes ./$(NAME)

asan: fclean
	@printf "$(BLUE)Compiling with AddressSanitizer...$(RESET)\n"
	@$(MAKE) --no-print-directory all CFLAGS="$(CFLAGS) -fsanitize=address"
	@printf "$(GREEN)✓ Compiled with Asan. Run ./$(NAME) to test.$(RESET)\n"

.PHONY: all clean fclean re valgrind asan
