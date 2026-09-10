/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bconejo- <bconejo-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/04 18:46:36 by bconejo-          #+#    #+#             */
/*   Updated: 2026/09/04 18:46:37 by bconejo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>	
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <errno.h>
# include <unistd.h>

# include "structs.h"
# include "environment.h"
# include "tokenizer.h"
# include "expander.h"
# include "cmd.h"
# include "status.h"
# include "shell.h"
# include "parser.h"
# include "utils.h"
# include "signals.h"

# include "builtins.h"
# include "executor.h"

# define BLUE "\033[34m" // azul
# define GRAY "\033[37m" // gris
# define RESET "\033[0m"
# define SOFT_YELLOW "\033[38;5;229m" // amarillo pastel
# define WARM_GRAY "\033[38;5;245m"   // gris cálido

#endif
