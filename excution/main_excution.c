/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_excution.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abounab <abounab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 18:21:23 by abounab           #+#    #+#             */
/*   Updated: 2024/07/02 14:52:08 by abounab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "excution.h"


/*

	*testers : https://docs.google.com/spreadsheets/u/0/d/1uJHQu0VPsjjBkR4hxOeCMEt3AOM1Hp_SmUzPFhAH-nA/htmlview?lsrp=1#gid=0

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


/*
	heredoc signal && any command after
*/



int	ft_perror(char *header, char *msg, int err)
{
	if (msg)
	{
		if (err)
		{
			if (header)
				write(STDERR_FILENO, header, ft_strlen(header));
			write(STDERR_FILENO, msg, ft_strlen(msg));
			write(STDERR_FILENO, "\n", 1);
			exit(err);
		}
		else
		{
			perror(msg);
			exit(errno);
		}
	}
	return (0);
}

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

int	open_heredoc(t_file *file, int outfile, t_env **env)
{
	char	*line;
	char	*tmp;

	write(STDOUT_FILENO, "> ", 2);
	line = get_next_line(STDIN_FILENO);
	while (line && !status && ft_strncmp(line, file->name[0], ft_strlen(line) - 1))
	{
		tmp = line;
		// check if it is allowed to expand it or not depends
		if (file->type == HERE_DOC_SIMPLE)
		{
			line = parsing_extend_var(line, *env, &status);
			free(tmp);
		}
		if (outfile != -1)
			write(outfile, line, ft_strlen(line));
		free(line);
		write(STDOUT_FILENO, "> ", 2);
		line = get_next_line(STDIN_FILENO);
	}
	// if (!line && status != 1)
	// 	write(STDERR_FILENO, "warning : here-document delimited by end-of-file\n", 49);
	if (outfile != -1)
		close(outfile);
	free(line);
	return (1);
}

int	last_file_position(t_file *files, t_type t)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (files)
	{
		if (files->type == HERE_DOC_SIMPLE || files->type == HERE_DOC_SPECIAL)
			i++;
		else if (files->type == t)
			j++;
		files = files->next;
	}
	if (t == HERE_DOC_SIMPLE || t == HERE_DOC_SPECIAL)
		return (i);
	return (j);
}

int	heredoc_management(t_file	*files, t_excute *node, t_env **env)
{
	int	heredoc_postion;
	int	i;
	int fd[2];
	
	i = 0;
	fd[1] = -1;
	heredoc_postion = last_file_position(files, HERE_DOC_SIMPLE) - 1;
	while (heredoc_postion >= 0 && files && !status)
	{
		if (i == heredoc_postion && (files->type == HERE_DOC_SIMPLE || files->type == HERE_DOC_SPECIAL))
		{
			if (pipe(fd) < 0)
				return (printf("%s\n", strerror(errno)), -1); //error handling
			dup2(fd[0], node->infile);
			close(fd[0]);
		}
		if ((files->type == HERE_DOC_SIMPLE || files->type == HERE_DOC_SPECIAL) && files->name)
		{
			open_heredoc(files, fd[1], env);
			if (status)
				return (0);
			i++;
		}
		files = files->next;
	}
	return (1);
}

t_excute	*heredoc_update(t_cmd *command, t_env **env)
{
	t_excute	*cmds;
	t_excute	*node;
	int			fds[2];

	cmds = NULL;
	if (command)
		fds[0] = dup(STDIN_FILENO);
	while (command)
	{
		node = cmd_create(fds[0]);
		if (!node)
			return (cmd_free(&cmds), NULL);
		if (command->next && pipe(fds) != -1) 
		{
			dup2(fds[1], node->outfile);
			close(fds[1]);
		}
		if (!heredoc_management(command->files, node, env))
			return (cmd_free(&cmds), NULL);
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
		// have to be handleded in the case of special builtins
		if (!files->name || files->name[1])
			return (ft_perror("minishell:", " ambiguous redirect", 1), -1);
		if (files->type == INFILE)
		{
			fd = open(files->name[0], INFILE);
			if (fd < 0)
				return (ft_perror(NULL, files->name[0], 0), fd) ;//error of file does not exist or no permission will be saved in the errno
			if (last_file_position(files, INFILE) > last_file_position(files, HERE_DOC_SIMPLE))
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
		// have to be handleded in the case of special builtins
		if (!files->name || files->name[1])
			return (ft_perror("minishell:", " ambiguous redirect", 1));//error  of ambigious by exit(1);
		if (files->type == OUFILE || files->type == APPEND)
		{
			fd = open(files->name[0], files->type, 0720);
			if (fd < 0)
				return (ft_perror(NULL, files->name[0], 0)) ;//error of no permission will be saved in the errno
			dup2(fd, cmds->outfile);
			close(fd);	
		}
		files = files->next;
	}
	return (1);
}

int	is_absolutecmd(char *cmd)
{
	int	i;
	char **paths;

	i = 0;
	paths = ft_split(getenv("PATH"), ':');
	while (paths && paths[i])
	{
		if (!ft_strncmp(cmd, paths[i], ft_strlen(paths[i])))
		{
			if (access(cmd, X_OK) != -1)
				return (free_array(&paths), 1);
			return (free_array(&paths), 0);
		}
		i++;
	}
	return (0);
}

int	get_path(char *cmd, char **paths)
{
	int	i;
	char *tmp;

	i = 0;
	while (cmd && paths && paths[i])
	{
		tmp = ft_strjoin(paths[i], cmd);
		if (!tmp)
			return (0);
		if (access(tmp, X_OK) != -1)
			return (free(tmp), i);
		free(tmp);
		i++;
	}
	return (0);
}

char **env_to_array(t_env *env)
{
	char	**arr;
	char	*joined;
	int		i;

	i = 0;
	arr = ft_calloc(env_size(env) + 1, sizeof(char *));
	if (!arr)
		return (0);
	while (env)
	{
		joined = ft_strjoin(env->key, "=");
		if (!joined)
			return (free_array(&arr), NULL);
		arr[i] = ft_strjoin(joined, env->value);
		if (!arr[i])
			return (free_array(&arr), NULL);
		free(joined);
		env = env->next;
		i++;
	}
	return arr;
}

char *get_commands(char **argv, char ***cmd_argv, char **paths)
{
	char	*cmd;
	char	*tmp;

	cmd = NULL;
	if (argv)
	{
		if (argv[0] && !ft_strncmp(argv[0], "/", 1) && is_absolutecmd(argv[0]))
			return (*cmd_argv = argv, free_array(&paths), ft_strdup(argv[0]));
		else if (argv[0] && !ft_strncmp(argv[0], "/", 1))
			return (free_array(&paths), ft_perror(argv[0], ": no such file or directory", 127), NULL);
		if (argv[0] && is_builtin(argv[0]))
			return (free_array(&paths), *cmd_argv = argv + 1, ft_strdup(argv[0]));
		cmd = ft_strjoin("/", argv[0]);
		if (!cmd)
			return (free_array(&paths), NULL);//error
		if (paths && get_path(cmd, paths))
		{
			tmp = cmd;
			cmd = ft_strjoin(paths[get_path(cmd, paths)], tmp);
			free(tmp);
			if (cmd)
				return (*cmd_argv = argv, free_array(&paths), cmd);
			return (free_array(&paths), NULL); //error 
		}
		free(cmd);
		free_array(&paths);
		if (!ft_strncmp("./", argv[0], 2))
		{
			if (access(argv[0], X_OK) != -1)
				return (*cmd_argv = argv, ft_strdup(argv[0]));
			return (free_array(&paths), ft_perror(NULL, argv[0] , 0), NULL);
		}
		return (free_array(&paths), ft_perror(argv[0], ": no such file or directory", 127), NULL);
	}
	return (free_array(&paths), ft_perror(argv[0], ": command not found", 1), NULL);
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

int	excute_cmd(t_excute *cmds, t_env **env, int child)
{
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
		if (execve(cmds->cmd, cmds->arguments, env_to_array(*env)) == -1)
			return (ft_perror(cmds->cmd, ": command not found", 127)); //error
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

int	close_other(t_excute *head, int pos)
{
	int	i;

	i = 0;
	while (head)
	{
		if (i != pos)
		{
			close(head->infile);
			close(head->outfile);
		}
		i++;
		head = head->next;
	}
	return (1);
}

void	signal_handler(int sig)
{
	(void) sig;
	status = 1;
	rl_replace_line("", 0);
	write (STDIN_FILENO, "\n", 1);
	rl_on_new_line();
	rl_redisplay();
}


int	ft_signals(int child)
{
	struct sigaction sa;

    sa.sa_handler = signal_handler;
    sa.sa_flags = 0;  // Do not restart functions if interrupted
    sigemptyset(&sa.sa_mask);
    if (child) {
        if (child == 1)
            sigaction(SIGINT, &sa, NULL); //first time
		else
			signal(SIGINT, SIG_IGN); //parent process when forked
		signal(SIGQUIT, SIG_IGN); //both
	}
	else
	{
		signal(SIGINT, SIG_DFL); // child process when forked
		signal(SIGQUIT, SIG_DFL);
	}
	return 1;
}

int	redirection_update(t_cmd *command, t_excute **head, t_env **env)
{
	int			pid;
	t_excute	*cmds;
	int			i;

	cmds = *head;
	i = 0;
	while (command && cmds)
	{
		if (!command->next && !(*head)->next && command->args && special_builtin(command->args[0], command->args[1]))
			child_excution(command, cmds, env, 0);
		else
		{
			pid = fork();
			ft_signals(pid);
			if (!pid)
				return (close_other(*head, i), child_excution(command, cmds, env, 1));
			if (pid && pid != -1)
				cmds->pid = pid;
			else
				return (status = 1, printf("%s\n", strerror(errno)));
		}
		cmds = cmds->next;
		command = command->next;
		i++;
	}
	return (close_other(*head, -1), 1);
}

int	waitprocess(t_excute *cmds)
{
	t_excute	*tmp;

	
	while (cmds)
	{
		if (cmds->pid)
		{
			if (cmds->pid)
				waitpid(cmds->pid, &status, 0);
			if (WIFSIGNALED(status))
				status = WTERMSIG(status) + 128;
			else
				status = WEXITSTATUS(status);
			cmd_free_node(cmds);
		}
		tmp = cmds->next;
		free(cmds);
		cmds = tmp;
	}
	return (1);
}



int	excution(t_cmd *command, t_env **env)
{
	t_excute	*cmds;

	cmds = heredoc_update(command, env);
	redirection_update(command, &cmds, env);
	waitprocess(cmds);
	return (1);
}


/*

	path .

*/