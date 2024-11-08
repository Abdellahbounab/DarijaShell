/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abounab <abounab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 14:16:27 by abounab           #+#    #+#             */
/*   Updated: 2024/07/16 11:15:15 by abounab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "../types.h"

int		ft_perror(char *header, char *msg, int err);

int		get_env(t_env **env, char **envp);

t_env	*env_getkey(t_env *lst, char *key);
int		env_unset(t_env **lst, char *key);
int		env_export(t_env **lst, char *key, char *val, char type);
int		env_addback(t_env **lst, t_env *newnode);
int		env_update(t_env **lst, char *key, char *newval, char newtype);
char	*env_getval(t_env *lst, char *key);
int		env_size(t_env *env);

int		free_env(t_env **env);
char	*join_strs(char **value);

int		is_builtin(char *cmd);
int		builtin_echo(t_excute *cmd);
int		builtin_pwd(t_env **env);
int		builtin_unset(t_env **env, t_excute *cmds);
int		builtin_env(t_env *env, int flag);
int		builtin_export(t_env **env, t_excute *cmds);
int		builtin_cd(t_env **env, t_excute *cmds);
int		builtin_exit(t_env **env, t_excute *cmds);

#endif