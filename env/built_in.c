/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abounab <abounab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 19:16:19 by abounab           #+#    #+#             */
/*   Updated: 2024/06/29 20:49:34 by abounab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "../parsing/parsing.h"
#include "../excution/excution.h"
#include "../types.h"

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
	if (cmd)
	{
		if (!ft_strcmp(cmd, "echo"))
			return (1);
		else if (!ft_strcmp(cmd, "cd"))
			return (1);
		else if (!ft_strcmp(cmd, "pwd"))
			return (1);
		else if (!ft_strcmp(cmd, "export"))
			return (1);
		else if (!ft_strcmp(cmd, "unset"))
			return (1);
		else if (!ft_strcmp(cmd, "env"))
			return (1);
		else if (!ft_strcmp(cmd, "exit"))
			return (1);
	}
	return (0);
}

int	builtin_echo(t_excute *cmd)
{
	char	flag;
	int		i;

	i = 0;
	flag = '\n';
	if (cmd->arguments && cmd->arguments[i] && !ft_strncmp(cmd->arguments[i], "-n", 2))
		flag = i++;
	while (cmd->arguments && cmd->arguments[i])
	{
		write(STDOUT_FILENO, cmd->arguments[i], ft_strlen(cmd->arguments[i]));
		if (cmd->arguments[i + 1])
			write(STDOUT_FILENO, " ", 1);
		i++;
	}
	write(STDOUT_FILENO, &flag, 1);
	exit(0);
}

int	builtin_cd(t_env **env, t_excute *cmds)
{
	char	str[100];

	if (env)//funciton that would check the existance of the path
	{
		if (cmds->arguments[0] && ft_strncmp(cmds->arguments[0], "~", ft_strlen(cmds->arguments[0])))
		{
			if (chdir(cmds->arguments[0]) < 0)
			{
				perror(cmds->arguments[0]);
				status = 1;
			}
		} 
		else
		{
			if (env_getval(*env, "HOME"))
				chdir(env_getval(*env, "HOME"));
			else
			{
				status = 1;
				write(STDERR_FILENO, "minishell: cd: HOME not set\n", 28);
			}
		}
		if (env_getkey(*env, "HOME"))
			env_export(env, "PWD", getcwd(str, 100));
		return 1;
	}
	else
		return (0);
}

int	builtin_pwd(t_env **env)
{
	//can be modified to have always the path even if it is not found on env
	char	str[100];

	if (env)
	{
		env_export(env, "PWD", getcwd(str, 100));
		write(STDOUT_FILENO, env_getval(*env, "PWD"), ft_strlen(env_getval(*env, "PWD")));
		write(STDOUT_FILENO, "\n", 1);
		exit(0);
	}
	exit(1);
}

int	builtin_unset(t_env **env, t_excute *cmds)
{
	int	i;
 
	i = 0;
	while (cmds->arguments && cmds->arguments[i])
		env_unset(env, cmds->arguments[i++]);
	return (1);
}

int	builtin_env(t_env *env, int flag)
{
	int	counter;

	counter = 0;
	while (env)
	{
		if (flag)
			write(STDOUT_FILENO, "	declare -x ", 12);
		write(STDOUT_FILENO, env->key, ft_strlen(env->key));
		write(STDOUT_FILENO, "=", 1);
		if (env->value)
			write(STDOUT_FILENO, env->value, ft_strlen(env->value));
		write(STDOUT_FILENO, "\n", 1);
		env = env->next;
		counter++;
	}
	exit(0);
}

int	builtin_export(t_env **env, t_excute *cmds)
{
	int	i;
	char **arr;
	char *str;

	i = 0;
	if (cmds->arguments && !cmds->arguments[0])
		return (builtin_env(*env, 1));
	while (cmds->arguments && cmds->arguments[i])
	{
		arr = ft_split(cmds->arguments[i], '=');
		if (!arr[0] || check_name(arr[0]) < 0)
			return (write(STDERR_FILENO, "export : not a valid identifier\n", 32), status = 1, 0);
		str = join_strs(arr + 1);
		env_export(env, arr[0], str);
		free_array(&arr);
		free(str);
		i++;
	}
	return (1);
}

int	is_numerique(char *str)
{
	int	i;
	int	len;

	i = 0;
	if (str)
		len = ft_strlen(str);
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str && str[i] && !ft_isdigit(str[i]))
		i++;
	if (str && len == i)
		return 1;
	return 0;
}

int	builtin_exit(t_env **env, t_excute *cmds)
{
	int	num;
	
	num = 0;
	if (cmds->arguments)
	{
		if (cmds->arguments[0])
			num = ft_atoi(cmds->arguments[0]);
		if (cmds->arguments[0] && !is_numerique(cmds->arguments[0]))
			ft_perror("exit : ", "numeric argument required", 255);
		if (cmds->arguments[0] && cmds->arguments[1])
		{
			status = 1;
			return (write (STDERR_FILENO, "exit: too many arguments\n", 25));
		}
	}
	free_env(env);
	write (STDIN_FILENO, "exit\n", 5);
	exit (num);
}
