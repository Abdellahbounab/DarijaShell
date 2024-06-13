/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_excution.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abounab <abounab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 18:21:23 by abounab           #+#    #+#             */
/*   Updated: 2024/06/13 20:07:59 by abounab          ###   ########.fr       */
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


int	read_excutelist(t_excute *cmds)
{
	if (!cmds)
		printf("null excut cmds\n");
	while (cmds)
	{
		printf("(%d, %d)\n", cmds->infile, cmds->outfile);
		cmds = cmds->next;
	}
	return 1;
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
	{
		*cmds = node;
		return (1);
	}
	while (cpy->next)
		cpy = cpy->next;
	cpy->next = node;
	return (1);
}

int	open_heredoc(char *heredoc, int outfile)
{
	char	*line;
	
	write(STDOUT_FILENO, ">", 1);
	printf("entrer %d >", outfile);
	line = get_next_line(STDIN_FILENO);
	while (line && ft_strncmp(line, heredoc, ft_strlen(heredoc)))
	{
		printf("outfile : %d\n", outfile);
		if (outfile != -1)
			write(outfile, line, ft_strlen(line));
		free(line);
		write(STDOUT_FILENO, ">", 1);
		line = get_next_line(STDIN_FILENO);
	}
	if (outfile != -1)
		close(outfile);
	free(line);
	return (1);
}

int	get_heredoc_position(t_file *files)
{
	int	i;

	i = 0;
	while (files)
	{
		if (files->type == HERE_DOC)
			i++;
		files = files->next;
	}
	return (i);
}

int	heredoc_management(t_file	*files, t_excute *node)
{
	int	heredoc_postion;
	int	i;
	int fd[2];
	
	i = 0;
	fd[0] = -1;
	heredoc_postion = get_heredoc_position(files) - 1;
	while (heredoc_postion >= 0 && files)
	{
		if (i == heredoc_postion && files->type == HERE_DOC)
		{
			if (pipe(fd) < 0)
				return (-1); //error handling
			// dup2(fd[1], node->infile);
			node->infile = fd[1];
			// close(fd[1]);
		}
		if (files->type == HERE_DOC)
		{
			open_heredoc(files->name[0], fd[0]);
			i++;
		}
		files = files->next;
	}
	return (1);
}

t_excute	*heredoc_update(t_cmd *command)
{
	t_excute	*cmds;
	t_excute	*node;
	int			fds[2];

	cmds = NULL;
	fds[1] = STDIN_FILENO;
	while (command)
	{
		node = cmd_create(fds[1]);
		if (!node)
			return (cmd_free(&cmds), NULL);
		if (command->next && pipe(fds) != -1)
			node->outfile = fds[0];
		heredoc_management(command->files, node);
		cmd_addback(&cmds, node);
		command = command->next;
	}
	return (cmds);
}

int	infile_update(t_file *files, t_excute *cmds)
{
	int	fd;

	fd = cmds->infile;
	while (files)
	{
		if (!files->name || files->name[1])
			return (printf("ambigious"), -1);//error  of ambigious by exit(1);
		if (files->type == INFILE)
		{
			printf("[%s]\n", files->name[0]);
			fd = open(files->name[0], INFILE);
			printf("fd : %d\n", fd);
			if (fd < 0)
				return (printf("fd no persmission or not exist"), fd) ;//error of file does not exist or no permission will be saved in the errno
			dup2(fd, cmds->infile);
			close(fd);
		}
		files = files->next;
	}
	return (1);
}

int	outfile_update(t_file *files, t_excute *cmds)
{
	int	fd;

	fd = cmds->outfile;
	while (files)
	{
		if (!files->name || files->name[1])
			return (-1);//error  of ambigious by exit(1);
		if (files->type == OUFILE || files->type == APPEND)
		{
			fd = open(files->name[0], files->type, 0720);
			if (fd < 0)
				return (printf("no permission\n"), -1) ;//error of no permission will be saved in the errno
			dup2(fd, cmds->outfile);
			close(fd);	
		}
		files = files->next;
	}
	return (1);
}

int	child_excution(t_cmd *command, t_excute *cmds, t_env **env)
{
	// check if ambigious redirect 
	(void)env;
	if (infile_update(command->files, cmds) < 0)
		return (exit(1), 0);//use errno to annonce the error depends if invalid files or ambigious
	if (outfile_update(command->files, cmds) < 0)
		return (exit(1), 0);//use errno to annonce the error depends if invalid files or ambigious
	close(cmds->infile);
	close(cmds->outfile);
	exit(0);
}

int	redirection_update(t_cmd *command, t_excute **head, t_env **env)
{
	int			pid;
	t_excute	*cmds;

	cmds = *head;
	while (command && cmds)
	{
		pid = fork();
		if (!pid)
			return (child_excution(command, cmds, env));
		if (pid && pid != -1)
			cmds->pid = pid;
		else
			return (0);//error handling	
		cmds = cmds->next;
		command = command->next;
	}
	return (1);
}

int	waitprocess(t_excute *cmds, int *status)
{
	while (cmds)
	{
		waitpid(cmds->pid, status, 0);
		if (cmds->infile)
			close(cmds->infile);
		cmd_free_node(cmds);
		cmds = cmds->next;
	}
	return (1);
}

int	excution(t_cmd *command, t_env *env, int *status)
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
	cmds = heredoc_update(command);
	redirection_update(command, &cmds, &env);
	waitprocess(cmds, status);
	printf("done process\n");
	return (1);
}
