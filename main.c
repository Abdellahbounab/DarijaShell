/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achakkaf <achakkaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 11:49:17 by achakkaf          #+#    #+#             */
/*   Updated: 2024/07/16 10:35:21 by achakkaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing/parsing.h"
#include "env/env.h"
#include "excution/excution.h"

int	main(int ac, char **av, char **envp)
{
	char	*line;
	t_cmd	*command;
	t_env	*env;

	(void)av;
	(void)ac;
	if (!get_env(&env, envp))
		return (ft_perror("minishell :", "error env", 127));
	while (1)
	{
		ft_signals(1);
		line = readline("minishell-$ ");
		if (!line)
			return (free_env(&env), g_status);
		add_history(line);
		command = parsing(line, env);
		excution(command, &env);
		free_cmd(command);
	}
	free_env(&env);
}
