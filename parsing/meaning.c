/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meaning.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achakkaf <achakkaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 11:21:18 by achakkaf          #+#    #+#             */
/*   Updated: 2024/06/02 21:19:11 by achakkaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

// [< , Makefile]                                           ->      filenames[Makefile]
// [<, Makefile, >, output, cat, -e, >, ou ] 				->		filesnames:[Makefile, output, ou], input: Makefile, ouput: ou
// [<, 'Makefile', >, "out"put, cat, -e, >, ou ]			->		filesnames:[Makefile, output, ou], input: Makefile, ouput: ou
// $arg=Make, [<, '$argfile', >, "out"put, cat, -e, >, ou ] ->		filesnames:[Makefile, output, ou], input: Makefile, ouput: ou

t_cmd *create_cmd(char **line, t_env *env, int *i)
{
	t_cmd *cmd;
	t_file *file;
	t_file *tmp_files;

	if (line == NULL)
		return (NULL);
	cmd = malloc(sizeof(t_cmd));
	if (cmd == NULL)
		return (NULL);
	cmd->args =NULL;
	cmd->files = NULL;
	cmd->next = NULL;
	cmd->path = NULL;
	cmd->status = NULL;
	while (line[*i])
	{
		if (ft_strcmp(line[*i], "|") == 0)
		{
			(*i)++;
			break;
		}
		else if (line[*i + 1] && ft_strcmp(line[*i], "<") == 0)
		{
			(*i)++;
			file = malloc(sizeof(t_file));
			if (file == NULL)
				return (NULL);
			file->name = filter(line[*i], env);
			file->type = infile;
			file->next = NULL;
			if (cmd->files == NULL)
				cmd->files = file;
			else
			{
				tmp_files = cmd->files;
				while(tmp_files->next)
					tmp_files = tmp_files->next;
				tmp_files->next = file;
			}	
		}
		else if (line[*i + 1] && ft_strcmp(line[*i], ">") == 0)
		{
			(*i)++;
			file = malloc(sizeof(t_file));
			if (file == NULL)
				return (NULL);
			file->name = filter(line[*i], env);
			file->type = oufile;
			file->next = NULL;
			if (cmd->files == NULL)
				cmd->files = file;
			else
			{
				tmp_files = cmd->files;
				while(tmp_files->next)
					tmp_files = tmp_files->next;
				tmp_files->next = file;
			}
		}
		else if (line[(*i) + 1] && ft_strcmp(line[*i], ">>") == 0)
		{
			(*i)++;
			file = malloc(sizeof(t_file));
			if (file == NULL)
				return (NULL);
			file->name = filter(line[*i], env);
			file->type = append;
			file->next = NULL;
			if (cmd->files == NULL)
				cmd->files = file;
			else
			{
				tmp_files = cmd->files;
				while(tmp_files->next)
					tmp_files = tmp_files->next;
				tmp_files->next = file;
			}
		}
		else if (line[*i + 1] && ft_strcmp(line[*i], "<<") == 0)
		{
			(*i)++;
			file = malloc(sizeof(t_file));
			if (file == NULL)
				return (NULL);
			file->name = filter(line[*i], env);
			file->type = here_doc;
			file->next = NULL;
			if (cmd->files == NULL)
				cmd->files = file;
			else
			{
				tmp_files = cmd->files;
				while(tmp_files->next)
					tmp_files = tmp_files->next;
				tmp_files->next = file;
			}
		}
		else
			cmd->args = append_array(cmd->args, line[*i]);
		(*i)++;
	}
	return (cmd);
}

char *filter(char *line, t_env *env)
{
	// t_cmd *cmd;
	t_env *tmp_env;
	int end;
	int start;
	char *tmp;
	char *var;
	char *token;
	char *tmp_token;
	char *tmp_all;
	char *tmp_join;

	end = 0;
	token = NULL;
	tmp_all = NULL;
	tmp_join = NULL;
	while (line && line[end])
	{
		if (line[end] == '\'')
		{
			end++;
			start = end;
			while (line[end] && line[end] != '\'')
				end++;
			tmp = ft_substr(line, start, end - start);
		}
		else if (line[end] == '"')
		{
			end++;
			start = end;
			while (line[end] && line[end] != '"')
			{
				if (line[end] == '$')
				{
					tmp_token = ft_substr(line, start, end - start);
					end++;
					start = end;
					while (line[end] && (ft_isalpha(line[end]) == GOOD || ft_isdigit(line[end]) == GOOD || line[end] == '_'))
						end++;
					var = ft_substr(line, start, end - start);
					tmp_env = env;
					while (tmp_env)
					{
						if (ft_strcmp(tmp_env->key, var) == GOOD)
						{
							tmp_token = ft_strjoin(tmp_token, tmp_env->value);
							break;
						}
						tmp_env = tmp_env->next;
					}
					tmp_all = ft_strjoin(tmp_all, tmp_token);
					// free(var);
					// free(tmp_token);
					start = end;
				}
				else 
					end++;
			}
			tmp_join = ft_substr(line, start, end++ - start);
			tmp = ft_strjoin(tmp_all, tmp_join);
			free(tmp_all);
			tmp_all = NULL;
		}
		else
		{
			start = end;
			while (line[end] && line[end] != '"' && line[end] != '\'')
			{
				if (line[end] == '$')
				{
					tmp_token = ft_substr(line, start, end - start);
					end++;
					start = end;
					while (line[end] && (ft_isalpha(line[end]) == GOOD || ft_isdigit(line[end]) == GOOD || line[end] == '_'))
						end++;
					var = ft_substr(line, start, end - start);
					tmp_env = env;
					while (tmp_env)
					{
						if (ft_strcmp(tmp_env->key, var) == GOOD)
						{
							tmp_token = ft_strjoin(tmp_token, tmp_env->value);
							break;
						}
						tmp_env = tmp_env->next;
					}
					tmp_all = ft_strjoin(tmp_all, tmp_token);
					// free(var);
					// free(tmp_token);
					start = end;
				}
				else 
					end++;
			}
			tmp_join = ft_substr(line, start, end - start);
			tmp = ft_strjoin(tmp_all, tmp_join);
			free(tmp_all);
			tmp_all = NULL;
		}
		// tmp_join = token;
		token = ft_strjoin(token, tmp);
		// free(tmp);
		// free(tmp_join);
	}
	return (token);
}

void add_back(t_cmd *head, t_cmd *next_command)
{
	t_cmd *tmp;

	if (head == NULL)
		head = next_command;
	else
	{
		tmp = head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = next_command;
	}
}

t_cmd *parse_cmds(char **split_cmd, t_env *env)
{
	int i;
	t_cmd *cmd;

	i = 0;
	cmd = create_cmd(split_cmd, env, &i);
	while (split_cmd && split_cmd[i])
	{
		// i++;
		add_back(cmd, create_cmd(split_cmd, env, &i));
	}
	return (cmd);
}