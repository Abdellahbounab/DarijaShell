/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excution.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abounab <abounab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 18:22:03 by abounab           #+#    #+#             */
/*   Updated: 2024/07/16 16:00:25 by abounab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXCUTION_H
# define EXCUTION_H

# include "../env/env.h"
# include "../getnextline/get_next_line_bonus.h"
# include "../parsing/parsing.h"
# include "../types.h"

int			ft_signals(int child);

int			excution(t_cmd *command, t_env **env);

int			ft_perror(char *header, char *msg, int err);

int			excute_cmd(t_excute *cmds, t_env **env, int child);

int			child_excution(t_cmd *command, t_excute *cmds, t_env **env,
				int child);

int			excute_builtin(t_excute *cmds, t_env **env, int child);

int			special_builtin(char *cmds, char *arr);

int			excution(t_cmd *command, t_env **env);

int			read_excutelist(t_excute *cmds);

char		**env_to_array(t_env *env);

int			is_absolutecmd(char *cmd);

int			close_other(t_excute *head, int pos);

void		open_heredoc(t_file *file, int outfile, t_env **env);

int			heredoc_management(t_file *files, t_env **env);

t_excute	*heredoc_update(t_cmd *command, t_env **env);

int			last_file_position(t_file *files, t_type t);

int			files_update(t_file *files, t_excute *cmds);

int			get_path(char *cmd, char **paths);

int			redirection_update(t_cmd *command, t_excute **head, t_env **env);

char		*get_commands(char **argv, char ***cmd_argv, char **paths);

int			waitprocess(t_excute *cmds);

int			cmd_free_node(t_excute *cpy);

int			cmd_free(t_excute **cmds);

int			ft_commandslen(t_cmd *command);

t_excute	*cmd_create(int inpipe);

int			cmd_addback(t_excute **cmds, t_excute *node);

char		**get_cmdarg(char **argv);

void		heredoc_signal(int sig);

#endif
