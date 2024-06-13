/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abounab <abounab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 19:16:19 by abounab           #+#    #+#             */
/*   Updated: 2024/06/13 22:22:23 by abounab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

/*
◦ echo with option -n
◦ cd with only a relative or absolute path
◦ pwd with no options
◦ export with no options
◦ unset with no options
◦ env with no options or arguments
◦ exit with no options
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

// int	builtin_echo(char *str, unsigned int flag_n)
// {
// 	// the flag_n have to be 0 if there is a flag else '\n'
// 	if (str)
// 		return (printf("%s%c", str, flag_n));
// 	return 0;
// }

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

// int	builtin_pwd(t_env *env)
// {
// 	if (env)
// 	{
// 		printf("%s\n", env_getval(env, "PWD"));
// 		return 1;
// 	}
// 	return 0;
// }

// int builtin_export(t_env *env, char *key, char *val)
// {
// 	// ihave to check the valid name
// 	env_export(env, key, val);
// }