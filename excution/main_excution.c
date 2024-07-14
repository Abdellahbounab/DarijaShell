/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_excution.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abounab <abounab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 18:21:23 by abounab           #+#    #+#             */
/*   Updated: 2024/07/14 22:37:10 by abounab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "excution.h"


int	excute_cmd(t_excute *cmds, t_env **env, int child)
{
	char	**arr;

	if (cmds && cmds->cmd && special_builtin(cmds->cmd, cmds->arguments[0]))
		return (excute_builtin(cmds, env, child));
	dup2(cmds->outfile, STDOUT_FILENO);
	close(cmds->outfile);
	dup2(cmds->infile, STDIN_FILENO);
	close(cmds->infile);
	if (is_builtin(cmds->cmd))
		return (excute_builtin(cmds, env, child));
	if (cmds && cmds->cmd && cmds->arguments)
	{
		arr = env_to_array(*env);
		if (!arr)
			return (ft_perror(NULL, "Memory", 0));
		if (execve(cmds->cmd, cmds->arguments, arr) == -1)
			// return (free_array(&arr), ft_perror(NULL, cmds->cmd, 0)); //error
			return (free_array(&arr), ft_perror(cmds->cmd, ": command not found", 127)); //error
	}
	return (0);
}

int	child_excution(t_cmd *command, t_excute *cmds, t_env **env, int child)
{
	if (infile_update(command->files, cmds) < 0)
		return (0);
	if (outfile_update(command->files, cmds) < 0)
		return (0);
	cmds->cmd = get_commands(command->args, &cmds->arguments, ft_split(env_getval(*env, "PATH"), ':'));
	if (excute_cmd(cmds, env, child))
		return (1);
	exit(1);
}

int	excute_builtin(t_excute *cmds, t_env **env, int child)
{
	if (cmds && cmds->cmd)
	{
		if (!ft_strcmp(cmds->cmd, "echo"))
			builtin_echo(cmds);
		else if (!ft_strcmp(cmds->cmd, "pwd"))
			builtin_pwd(env);
		else if (!ft_strcmp(cmds->cmd, "env"))
			builtin_env(*env, 0);
		else if (!ft_strcmp(cmds->cmd, "unset"))
			builtin_unset(env, cmds);
		else if (!ft_strcmp(cmds->cmd, "export"))
			builtin_export(env, cmds);
		else if (!ft_strcmp(cmds->cmd, "exit"))
			builtin_exit(env, cmds);
		else if (!ft_strcmp(cmds->cmd, "cd"))
			builtin_cd(env, cmds);
		if (child)
			exit(errno);
		free(cmds->cmd);
	}
	return (1);
}

int	special_builtin(char *cmds, char *arr)
{
	if (cmds)
	{
		if (cmds &&!ft_strcmp(cmds, "unset"))
			return 1;
		else if (cmds && arr && !ft_strcmp(cmds, "export"))
			return 1;
		else if (cmds && !ft_strcmp(cmds, "exit"))
			return 1;
		else if (cmds && !ft_strcmp(cmds, "cd"))
			return 1;
	}
	return 0;
}

int	excution(t_cmd *command, t_env **env)
{
	t_excute	*cmds;

	cmds = heredoc_update(command, env);
	redirection_update(command, &cmds, env);
	waitprocess(cmds);
	return (1);
}
