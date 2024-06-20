/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abounab <abounab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 19:16:19 by abounab           #+#    #+#             */
/*   Updated: 2024/06/20 20:59:32 by abounab          ###   ########.fr       */
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
	if (cmd && !ft_strncmp(cmd, "echo", 4))
		return (1);
	else if (cmd && !ft_strncmp(cmd, "cd", 2))
		return (1);
	else if (cmd && !ft_strncmp(cmd, "pwd", 3))
		return (1);
	else if (cmd && !ft_strncmp(cmd, "export", 6))
		return (1);
	else if (cmd && !ft_strncmp(cmd, "unset", 5))
		return (1);
	else if (cmd && !ft_strncmp(cmd, "env", 3))
		return (1);
	else if (cmd && !ft_strncmp(cmd, "exit", 4))
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
		write(cmd->outfile, cmd->arguments[i], ft_strlen(cmd->arguments[i]));
		if (cmd->arguments[i + 1])
			write(cmd->outfile, " ", 1);
		i++;
	}
	write(cmd->outfile, &flag, 1);
	return (1);
}

int	builtin_cd(t_env **env, t_excute *cmds)
{
	char	str[100];
	// if (env && path_exist(path))//funciton that would check the existance of the path
	if (env)//funciton that would check the existance of the path
	{
		if (cmds->arguments[0])
			chdir(cmds->arguments[0]);
		else
		{
			if (env_getval(*env, "HOME"))
				chdir(env_getval(*env, "HOME"));
			else
				chdir("/");
		}
		env_export(env, "PWD", getcwd(str, 100));
		return 1;
	}
	else
		// errno(no file or directory exist)
		return 0;
}

int	builtin_pwd(t_excute *cmds, t_env **env)
{
	//can be modified to have always the path even if it is not found on env
	char	str[100];

	if (env)
	{
		env_export(env, "PWD", getcwd(str, 100));
		write(cmds->outfile, env_getval(*env, "PWD"), ft_strlen(env_getval(*env, "PWD")));
		write(cmds->outfile, "\n", 1);
		return 1;
	}
	return (0);
}

int	builtin_unset(t_env **env, t_excute *cmds)
{
	// have to be protected since it does seg when unsetting hte first env or it may be other cases
	int	i;

	i = 0;
	while (cmds->arguments && cmds->arguments[i])
	{
		*env = env_unset(*env, cmds->arguments[i]);
		printf("%p\n", env);
		i++;
	}
	return (1);
}

int	builtin_env(t_excute *cmds, t_env *env)
{
	int	counter;

	counter = 0;
	while (env)
	{
		write(cmds->outfile, env->key, ft_strlen(env->key));
		write(cmds->outfile, "=", 1);
		if (env->value)
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
	if (cmds->arguments && !cmds->arguments[0])
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