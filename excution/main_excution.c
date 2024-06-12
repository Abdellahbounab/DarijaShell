/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_excution.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abounab <abounab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 18:21:23 by abounab           #+#    #+#             */
/*   Updated: 2024/06/12 15:33:53 by abounab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "excution.h"


/*
	command : 	**agrs = {cmd , args...}
				*path = path of cmd
				*status = integer of exit status
				**files = {**name + type of file, ....}

	env		:	*key = key name
				*value = value of the key

	excute	:	*cmd = path+cmd;
				**arguments = wrgs of cmd;
				infile = fd input;
				outfile = fd output;
*/

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
int	cmd_free_node(t_excute *cpy)
{
	int	i;

	i = 0;
	while (cpy->arguments[i])
		free(cpy->arguments[i++]);
	free(cpy->arguments);
	free(cpy->cmd);
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

t_excute	*cmd_create(int inpipe)
{
	t_excute	*cmd;

	cmd = ft_calloc(1, sizeof(t_excute));
	if (!cmd)
		return (0);
	cmd->infile = inpipe;
	cmd->outfile = STDOUT_FILENO;
	return (cmd);
}

int	cmd_addback(t_excute **cmds, t_excute *node)
{
	t_excute	*cpy;

	cpy = *cmds;
	if (!node)
		return (0);
	if (!cpy)
		return (cpy = node, 1);
	while (cmds && cpy && cpy->next)
		cpy = cpy->next;
	cpy->next = node;
	return (1);
}

int	update_heredocs(t_cmd	*cmd, t_excute *node)
{
	char	*heredoc;
	char	*line;

	heredoc = NULL;
	while (cmd->files)
	{
		if (cmd->files->type == HERE_DOC)
			heredoc = cmd->files->name[0];
		cmd->files = cmd->files->next;
	}
	if (!heredoc)
		return (1);
	write(STDOUT_FILENO, ">", 1);
	line = get_next_line(STDIN_FILENO);
	while (line && ft_strncmp(line, heredoc, ft_strlen(heredoc)))
	{
		write(node->outfile, line, ft_strlen(line));
		write(STDOUT_FILENO, ">", 1);
		line = get_next_line(STDIN_FILENO);
	}
	return (1);
}

t_excute	*update_ridirection(t_cmd *command)
{
	t_excute	*cmds;
	t_excute	*node;
	int			fds[2];

	cmds = NULL;
	fds[1] = 0;
	while (command)
	{
		node = cmd_create(fds[1]);
		if (!node)
			return (cmd_free(&cmds), NULL);
		if (command->next && pipe(fds) != -1)
			node->outfile = fds[0];
		update_heredocs(command, node);
		cmd_addback(&cmds, node);
		command = command->next;
	}
	return (cmds);
}

int	excution(t_cmd *command, t_env *env)
{
	// 1 - starting by files
	// important :ihave to open all heredocs first and get the input of whetevr cmd i have 
	// 		for inputfiles , we check for the last herdoc we use before opening other files , 
	// 				then if herdoc is not the last file of input files , we wont use it but we return if the files are valid then we use the last input of them
	// 		for output of append file we wont check if file exist but we only gonna user flag of creat or append + create in case
	// 2 - verifie the cmd (would be 1st string in args) + get its path in *path
	// 3 - after we get its commands and all args after verification or return errno with exit status
	// 4 - we fork to excute out command using the pipe if command->next is not null , means that theire is other commands
	
	// ihave to pipe if multiple cmd before fork and dup2 the input/ ihave to fork for each node of cmd / this is where iwould get each command in a new t_excute linkedList (get) + ihave to register the pid of the fork in each command in a array of pids
	t_excute	*cmds;
	
	env = NULL;
	cmds = update_ridirection(command);
	return (1);
}
