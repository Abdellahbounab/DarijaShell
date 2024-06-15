/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abounab <abounab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 19:16:19 by abounab           #+#    #+#             */
/*   Updated: 2024/06/15 22:27:57 by abounab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "../parsing/parsing.h"

/*
◦ echo with option -n *
◦ cd with only a relative or absolute path
◦ pwd with no options *
◦ export with no options (when no arg can display the envs) *
◦ unset with no options * 
◦ env with no options or arguments *
◦ exit with no options *
*/


int	is_builtin(char *cmd)
{
	int	len;
	
	len = ft_strlen(cmd);
	if (cmd && !ft_strncmp(cmd, "echo", len))
		return (1);
	else if (cmd && !ft_strncmp(cmd, "cd", len))
		return (1);
	else if (cmd && !ft_strncmp(cmd, "pwd", len))
		return (1);
	else if (cmd && !ft_strncmp(cmd, "export", len))
		return (1);
	else if (cmd && !ft_strncmp(cmd, "unset", len))
		return (1);
	else if (cmd && !ft_strncmp(cmd, "env", len))
		return (1);
	else if (cmd && !ft_strncmp(cmd, "exit", len))
		return (1);
	return (0);
}

int	builtin_echo(t_excute *cmd)
{
	// the flag_n have to be 0 if there is a flag else '\n'
	char	flag;
	int		i;

	i = 0;
	flag = '\n';
	if (cmd->arguments && cmd->arguments[i] && !ft_strncmp(cmd->arguments[i], "-n", ft_strlen(cmd->arguments[i])))
		flag = i++;
	while (cmd->arguments && cmd->arguments[i])
	{
		// printf("%s", cmd->arguments[i]);
		write(cmd->outfile, cmd->arguments[i], ft_strlen(cmd->arguments[i]));
		if (cmd->arguments[i + 1])
			write(cmd->outfile, " ", 1);
		i++;
	}
	write(cmd->outfile, &flag, 1);
	return (1);
}

// int	builtin_cd(t_env **env, char *path)
// {
// 	if (env && path_exist(path))//funciton that would check the existance of the path
// 	{
// 		env_update(env, "OLDPWD", env_getval(env, "PWD"));
// 		env_update(env, "PWD", path);
// 		// funciton that would change our directory
// 		return 1;
// 	}
// 	else
// 		// errno(no file or directory exist)
// 		return 0;
// }

int	builtin_pwd(t_excute *cmds, t_env *env)
{
	char	*pwd;
	//can be modified to have always the path even if it is not found on env

	if (env)
	{
		pwd = env_getval(env, "PWD");
		write(cmds->outfile, pwd, ft_strlen(pwd));
		write(cmds->outfile, "\n", 1);
		free(pwd);
		return 1;
	}
	return (0);
}

int	builtin_unset(t_env **env, t_excute *cmds)
{
	int	i;

	i = 0;
	while (cmds->arguments && cmds->arguments[i])
	{
		env_unset(env, cmds->arguments[i]);
		i++;
	}
	return (1);
}

// int builtin_export(t_env *env, char *key, char *val)
// {
// 	// ihave to check the valid name
// 	env_export(env, key, val);
// }

int	builtin_env(t_excute *cmds, t_env *env)
{
	int	counter;

	counter = 0;
	while (env)
	{
		write(cmds->outfile, env->key, ft_strlen(env->key));
		write(cmds->outfile, "=", 1);
		write(cmds->outfile, env->value, ft_strlen(env->value));
		write(cmds->outfile, "\n", 1);
		env = env->next;
		counter++;
	}
	return (counter);
}

int	builtin_export(t_env **env, t_excute *cmds)
{
	int	i;
	char **arr;
	char *str;

	i = 0;
	if (!cmds->arguments)
		return (builtin_env(cmds, *env));
	while (cmds->arguments && cmds->arguments[i])
	{
		arr = ft_split(cmds->arguments[i], '=');
		str = join_strs(arr + 1);
		env_export(env, arr[0], str);
		free_array(&arr);
		free(str);
		i++;
	}
	return (1);
}