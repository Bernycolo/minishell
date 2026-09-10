/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bconejo- <bconejo-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/04 18:41:39 by bconejo-          #+#    #+#             */
/*   Updated: 2026/09/04 18:41:40 by bconejo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "structs.h"

t_status	is_builtin(t_cmd *cmd);
void		exec_builtin(t_shell *shell);

void		builtin_cd(t_shell *msh);
void		builtin_echo(t_shell *msh);
void		builtin_env(t_shell *msh);
void		builtin_exit(t_shell *shell);
void		builtin_export(t_shell *msh);
void		builtin_pwd(t_shell *msh);
void		builtin_unset(t_shell *msh);

#endif