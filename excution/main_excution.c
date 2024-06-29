/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_excution.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abounab <abounab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 18:21:23 by abounab           #+#    #+#             */
/*   Updated: 2024/06/29 12:45:52 by abounab          ###   ########.fr       */
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

// int	free_array(&char **paths)
// {
// 	int	i;

// 	i = 0;
// 	while(paths && paths[i])
// 		free(paths[i++]);
// 	free(paths);
// 	return (1);
// }

int			raed_array(char **paths)
{
	int i;

	i = 0;
	while (paths && paths[i])
		printf(" %s ", paths[i++]);
	return printf("\n");
}



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

int	open_heredoc(char *heredoc, int outfile, t_env **env, int *status)
{
	char	*line;
	char	*tmp;

	write(STDOUT_FILENO, ">", 1);
	line = get_next_line(STDIN_FILENO);
	while (line && !status && ft_strncmp(line, heredoc, ft_strlen(line) - 1))
	{
		tmp = line;
		line = parsing_extend_var(line, *env, status);
		free(tmp);
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

int	heredoc_management(t_file	*files, t_excute *node, t_env **env, int *status)
{
	int	heredoc_postion;
	int	i;
	int fd[2];
	
	i = 0;
	fd[1] = -1;
	heredoc_postion = get_heredoc_position(files) - 1;
	while (heredoc_postion >= 0 && files)
	{
		if (i == heredoc_postion && files->type == HERE_DOC)
		{
			if (pipe(fd) < 0)
				return (-1); //error handling
			dup2(fd[0], node->infile);
			close(fd[0]);
		}
		if (files->type == HERE_DOC)
		{
			open_heredoc(files->name[0], fd[1], env, status);
			i++;
		}
		files = files->next;
	}
	return (1);
}

t_excute	*heredoc_update(t_cmd *command, t_env **env, int *status)
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
			dup2(fds[1], node->outfile); //it does output in the 1 to be read by 0
			close(fds[1]);
		}
		heredoc_management(command->files, node, env, status); //heredoc
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
			if (!files->next)
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

int	is_absolutecmd(char *cmd, char **paths)
{
	int	i;

	i = 0;
	while (paths && paths[i])
	{
		if (!ft_strncmp(cmd, paths[i], ft_strlen(paths[i])))
		{
			if (access(cmd, X_OK) != -1)
				return (1);
			return (0);
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
		if (argv[0] && is_builtin(argv[0]))
			return (free_array(&paths), *cmd_argv = argv + 1, ft_strdup(argv[0]));//check if some of my builtins to be excuted , wont need a path
		else if (paths)
		{
			if (is_absolutecmd(argv[0], paths))
				return (*cmd_argv = argv, free_array(&paths), ft_strdup(argv[0]));
			cmd = ft_strjoin("/", argv[0]); //ex if ls : it wil be /ls to be used later when joining the paths
			if (!cmd)
				return (free_array(&paths), NULL);//error
			if (get_path(cmd, paths))
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
			if (!ft_strncmp("./", argv[0], 2) && access(argv[0], X_OK) != -1)
				return (*cmd_argv = argv, ft_strdup(argv[0]));
			// return (ft_perror(NULL, argv[0], 0), NULL);
			return (*cmd_argv = argv, ft_strdup(argv[0]));
		}
	}
	return (free_array(&paths), ft_perror(argv[0], ": command not found", 1), NULL);
}

int	excute_builtin(t_excute *cmds, t_env **env)
{
	int len;

	if (cmds && cmds->cmd)
	{
		len = ft_strlen(cmds->cmd);
		if (!ft_strncmp(cmds->cmd, "echo", len))
			builtin_echo(cmds);
		else if (!ft_strncmp(cmds->cmd, "pwd", len))
			builtin_pwd(env);
		else if (!ft_strncmp(cmds->cmd, "env", len))
			builtin_env(*env, 0);
		else if (!ft_strncmp(cmds->cmd, "unset", len))
			builtin_unset(env, cmds);
		else if (!ft_strncmp(cmds->cmd, "export", len))
			builtin_export(env, cmds);
		else if (!ft_strncmp(cmds->cmd, "exit", len))
			builtin_exit(env, cmds);
		else if (!ft_strncmp(cmds->cmd, "cd", len))
			builtin_cd(env, cmds);
	}
	return (1);
}

int	special_builtin(char *cmds, char *arr)
{
	int len;

	if (cmds)
	{
		len = ft_strlen(cmds);
		if (cmds &&!ft_strncmp(cmds, "unset", len))
			return 1;
		else if (cmds && arr && !ft_strncmp(cmds, "export", len))
			return 1;
		else if (cmds && !ft_strncmp(cmds, "exit", len))
			return 1;
		else if (cmds && !ft_strncmp(cmds, "cd", len))
			return 1;
	}
	return 0;
}

int	excute_cmd(t_excute *cmds, t_env **env)
{
	if (cmds && cmds->cmd && special_builtin(cmds->cmd, cmds->arguments[0]))
		return (excute_builtin(cmds, env));
	dup2(cmds->outfile, STDOUT_FILENO);
	close(cmds->outfile);
	dup2(cmds->infile, STDIN_FILENO);
	close(cmds->infile);
	if (is_builtin(cmds->cmd))
		return (excute_builtin(cmds, env));
	if (cmds && cmds->cmd && cmds->arguments)
	{
		if (execve(cmds->cmd, cmds->arguments, env_to_array(*env)) == -1)
			return (ft_perror(cmds->cmd, ": command not found", 127)); //error`
	}
	return (0);
}

int	child_excution(t_cmd *command, t_excute *cmds, t_env **env)
{
	if (infile_update(command->files, cmds) < 0)
		return (0);
	if (outfile_update(command->files, cmds) < 0)
		return (0);
	cmds->cmd = get_commands(command->args, &cmds->arguments, ft_split(env_getval(*env, "PATH"), ':'));
	if (excute_cmd(cmds, env))
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
	// exit status have to be edited depends on if same process or child process
	// have to handle heredoc signal
	write (STDOUT_FILENO, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}


int	ft_signals(int child)
{
	if (child)
	{
		if (child == 1)
			signal(SIGINT, signal_handler);
		else
			signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
	else
		signal(SIGINT, SIG_DFL);
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
		if (command->args && special_builtin(command->args[0], command->args[1]))
			child_excution(command, cmds, env);
		else
		{
			pid = fork();
			ft_signals(pid);
			if (!pid)
				return (close_other(*head, i), child_excution(command, cmds, env));
			if (pid && pid != -1)
				cmds->pid = pid;
			else
				return (ft_perror(NULL, "Malloc", 1));//error handling	
		}
		cmds = cmds->next;
		command = command->next;
		i++;
	}
	return (close_other(*head, -1), 1);
}

int	waitprocess(t_excute *cmds, int *status)
{
	while (cmds)
	{
		if (cmds->pid)
		{
			if (cmds->pid)
				waitpid(cmds->pid, status, 0);
			if (WIFSIGNALED(*status))
				*status = 130;
			else
				*status = WEXITSTATUS(*status);
			cmd_free_node(cmds);
		}
		cmds = cmds->next;
	}
	return (1);
}



int	excution(t_cmd *command, t_env **env, int *status)
{
	t_excute	*cmds;
	
	cmds = heredoc_update(command, env, status);
	redirection_update(command, &cmds, env);
	waitprocess(cmds, status);
	return (1);
}
