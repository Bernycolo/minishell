/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bconejo- <bconejo-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/04 18:47:13 by bconejo-          #+#    #+#             */
/*   Updated: 2026/09/04 18:47:14 by bconejo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_redir		t_redir;
typedef struct s_cmd		t_cmd;
typedef struct s_env		t_env;
typedef struct s_token		t_token;
typedef struct s_shell		t_shell;

typedef enum e_token_type	t_token_type;
typedef enum e_pstate		t_pstate;
typedef enum e_status		t_status;
typedef enum e_signal		t_signal;

#endif