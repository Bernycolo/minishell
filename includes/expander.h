/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bconejo- <bconejo-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/04 18:42:04 by bconejo-          #+#    #+#             */
/*   Updated: 2026/09/04 18:42:05 by bconejo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "structs.h"

char	*extract_single_quoted(char *value, int *i);
char	*extract_double_quoted(char *value, int *i, t_env *env,
			int last_status);
char	*expand_tilde(int *i, t_env *env);
char	*expand_variable(char *value, int *i, t_env *env, int last_status);
char	*extract_plain_text(char *value, int *i);
void	expand_tokens(t_token **list, t_env *env, int last_status);
char	*expand_group(char *value, int *i, t_env *env, int last_status);

#endif