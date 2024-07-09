/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_excution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achakkaf <achakkaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 10:24:39 by achakkaf          #+#    #+#             */
/*   Updated: 2024/07/09 10:26:34 by achakkaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "excution.h"

int	cmd_free_node(t_excute *cpy)
{
	int	i;

	i = 0;
	while (cpy && cpy->arguments && cpy->arguments[i])
		free(cpy->arguments[i++]);
	free(cpy->arguments);
	free(cpy->cmd);
	cpy = NULL;
	return (1);
}

int	cmd_free(t_excute **cmds)
{
	t_excute *cpy;

	cpy = *cmds;
	while (cpy)
	{
		cmd_free_node(cpy);
		cpy = cpy->next;
	}
	free(*cmds);
	return (1);
}

int	ft_commandslen(t_cmd *command)
{
	int	counter;

	counter = 0;
	while (command)
	{
		counter++;
		command = command->next;
	}
	return	counter;
}

t_excute	*cmd_create(int inpipe)
{
	t_excute	*cmd;

	cmd = ft_calloc(1, sizeof(t_excute));
	if (!cmd)
		return (0);
	cmd->infile = dup(inpipe);
	close(inpipe);
	cmd->outfile = dup(STDOUT_FILENO);
	return (cmd);
}

int	cmd_addback(t_excute **cmds, t_excute *node)
{
	t_excute	*cpy;

	cpy = *cmds;
	if (!node)
		return (0);
	if (!cpy)
	{
		*cmds = node;
		return (1);
	}
	while (cpy->next)
		cpy = cpy->next;
	cpy->next = node;
	return (1);
}
