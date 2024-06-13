/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abounab <abounab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 14:16:27 by abounab           #+#    #+#             */
/*   Updated: 2024/06/13 22:05:38 by abounab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
#define ENV_H

#include "../types.h"

int	get_env(t_env **env, char **envp);
t_env *env_getkey(t_env *lst, char *key);
int	env_unset(t_env **lst, char *key);
int	env_read(t_env *lst);
int	env_export(t_env **lst, char *key, char *val);
int	env_addback(t_env **lst, t_env *newnode);
int	env_update(t_env **lst, char *key, char *newval);
char *env_getval(t_env *lst, char *key);

int	is_builtin(char *cmd);

#endif