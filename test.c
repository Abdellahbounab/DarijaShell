
#include "parsing.h"

// , "SECURITYSESSIONID=186a8"
// , "USER=achakkaf"
// , "MallocNanoZone=0"
// , "COMMAND_MODE=unix2003"
// , "SHELL=/bin/zsh"
// , "LaunchInstanceID=FAAC1BAA-F040-4F08-9871-74038559C113"
// , "__CF_USER_TEXT_ENCODING=0x18C0F:0x0:0x0"
// , "XPC_SERVICE_NAME=0"
// , "SSH_AUTH_SOCK=/private/tmp/com.apple.launchd.85iQXN54hh/Listeners"
// , "XPC_FLAGS=0x0"
// , "LOGNAME=achakkaf"
// , "TMPDIR=/var/folders/zz/zyxvpxvq6csfxvn_n000cc1w00330g/T/"
// , "ORIGINAL_XDG_CURRENT_DESKTOP=undefined"
// , "SHLVL=1"
// , "PWD=/Users/achakkaf/Desktop/minishell"
// , "OLDPWD=/Users/achakkaf/Desktop/minishell/mylib"
// , "TERM_PROGRAM=vscod"
// , "TERM_PROGRAM_VERSION=1.85.0"
// , "LANG=en_US.UTF-8"
// , "COLORTERM=truecolor"
// , "GIT_ASKPASS=/Applications/Visual Studio Code.app/Contents/Resources/app/extensions/git/dist/askpass.sh"
// , "VSCODE_GIT_ASKPASS_NODE=/Applications/Visual Studio Code.app/Contents/Frameworks/Code Helper (Plugin).app/Contents/MacOS/Code Helper (Plugin)"
// , "ZDOTDIR=/Users/achakkaf"
// , "USER_ZDOTDIR=/Users/achakkaf"
// , "TERM=xterm-256color"
// , "_=/usr/bin/env"

int main()
{
	// // int pid;
	// // char *env[30] = {
	// //   "PATH=/Applications/Visual Studio Code.app/Contents/Resources/app/bin:/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki:/Applications/Visual Studio Code.app/Contents/Resources/app/bin"
	// // , "HOME=/Users/achakkaf"
	// // };
	int i;
	char *line;
	char **cmd;
	t_command *command;
	// execv("/bin/ls",cmd);
	while (1)
	{
		line = readline("minishell-$ ");
		add_history(line);
	// 	// printf("%s\n",line);
	// 	// printf("|%s|\n", filtre_quote(line));
		cmd = split_cmd(line);
		// i = 0;
		// while (cmd && cmd[i] != NULL)
		// 	printf("|%s|\n", cmd[i++]);
	// 	// cmd = append_array(NULL, "cat");
	// 	// i = 0;
	// 	// while (cmd && cmd[i] != NULL)
	// 	// 	printf("|%s|\n", cmd[i++]);
	// 	// if (cmd == NULL)
	// 	// 	continue;
		command = create_cmd_linked_list(cmd);
		while (command)
		{
			printf("append:%d\ninput:%s\noutput:%s\npath:%s\n", command->append, command->input_files, command->output_files, command->path);
			printf("limitor:%s\nheredoc:%d\n", command->limitor, command->heredoc);
			i = 0;
			while (command->args && command->args[i] != NULL)
				printf("|%s|\n", command->args[i++]);
			command = command->next;
		}
	// 	// if (ft_strcmp("exit", line))
	// 	// 	exit(0);
	// 	// pid = fork();
	// 	// if (pid == 0)
	// 	// wait(NULL);
	}
	// char *str = malloc (0);
	// int fd;
	// fd = open("parsing.h", O_CREAT | O_RDWR, 0644);
	// dup2(fd, 0);
	// exec_command(NULL, NULL);
	// if (str == NULL)
	// {	printf("sdfds\n");
	// 	return(1);}
}
