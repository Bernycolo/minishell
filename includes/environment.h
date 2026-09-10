/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bconejo- <bconejo-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/04 18:41:54 by bconejo-          #+#    #+#             */
/*   Updated: 2026/09/04 18:41:55 by bconejo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIRONMENT_H
# define ENVIRONMENT_H

# include "structs.h"

/**
 * @struct s_env
 * @brief Represents a node of the environment linked list
 * 
 */
typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

t_env				*new_env(const char *key, const char *value);
void				add_env(t_env **list, t_env *new);
char				*env_get(t_env *env, const char *key);
void				env_set(t_env **env, const char *key, const char *value);
void				env_unset(t_env **env, const char *key);
void				env_init(t_env **list, char **envp);
void				free_env(t_env **env);

#endif
