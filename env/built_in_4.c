/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abounab <abounab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 10:51:35 by abounab           #+#    #+#             */
/*   Updated: 2024/07/16 11:00:30 by abounab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../excution/excution.h"
#include "../parsing/parsing.h"
#include "env.h"

static int	is_numerique(char *str, int res)
{
	int	i;
	int	len;
	int	sign;

	i = 0;
	sign = 0;
	if (str)
		len = ft_strlen(str);
	if (str[i] && (str[i] == '-' || str[i] == '+') && str[i + 1])
	{
		i++;
		sign++;
	}
	while (str && str[i] && !ft_isdigit(str[i]))
		i++;
	if (str && len != i)
		return (0);
	if (len > 20 
		|| (len == 20 && !res && ft_strcmp(str, "-9223372036854775808")))
		return (0);
	else if (len == 19 + sign && res == -1 && ft_strcmp(str + sign,
			"9223372036854775807"))
		return (0);
	return (1);
}

int	builtin_exit(t_env **env, t_excute *cmds)
{
	int		num;
	char	*arg;

	num = g_status;
	arg = NULL;
	if (cmds->arguments)
	{
		if (cmds->arguments[0])
		{
			arg = ft_strtrim(cmds->arguments[0], " \t");
			if (arg)
				num = ft_atoi(arg);
		}
		if (arg && !is_numerique(arg, num))
			ft_perror("exit : ", "numeric argument required", 255);
		if (cmds->arguments[0] && cmds->arguments[1])
		{
			g_status = 1;
			return (write(STDERR_FILENO, "exit: too many arguments\n", 25));
		}
	}
	free_env(env);
	write(STDIN_FILENO, "exit\n", 5);
	exit(num);
}
