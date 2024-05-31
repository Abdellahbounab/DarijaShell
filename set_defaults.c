/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_defaults.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achakkaf <achakkaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 12:02:58 by achakkaf          #+#    #+#             */
/*   Updated: 2024/05/31 17:08:38 by achakkaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void add_back(t_command *head, t_command *next_command)
{
	t_command *tmp;

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

t_command *set_command(char **split_cmd, int *i)
{
	t_command *command;

	if (split_cmd == NULL)
		return (NULL);
	command = malloc(sizeof(t_command));
	if (command == NULL)
		return (NULL);
	command->append = 0;
	command->args = NULL;
	command->path = NULL;
	command->input_files = NULL;
	command->output_files = NULL;
	command->next = NULL;
	command->limitor = NULL;
	command->heredoc = 0;
	while (split_cmd[*i] && ft_strcmp(split_cmd[*i], "|"))
	{
		if (ft_strcmp(split_cmd[*i], "<") == 0)
		{
			free(command->input_files);
			command->input_files = filtre_quote(split_cmd[++(*i)]); // change it this is this is a problem "Make""file" this is valid
			command->heredoc = 0;
		}
		else if (ft_strcmp(split_cmd[*i], ">") == 0)
		{
			command->output_files = filtre_quote(split_cmd[++(*i)]);
			command->append = 0;
		}
		else if (ft_strcmp(split_cmd[*i], ">>") == 0)
		{
			command->output_files = filtre_quote(split_cmd[++(*i)]);
			command->append = 1;
		}
		else if (ft_strcmp(split_cmd[*i], "<<") == 0)
		{
			command->limitor = filtre_quote(split_cmd[++(*i)]);
			command->heredoc = 1;
			free(command->input_files);
			command->input_files = NULL;
		}
		else if (ft_strcmp(split_cmd[*i], "\n"))
		{
			printf("split_cmd: |%s|\n", ft_strchr(split_cmd[*i], '<'));
			command->args = append_array(command->args, filtre_quote(split_cmd[*i]));
		}
		(*i)++;
	}
	return (command);
}

t_command *create_cmd_linked_list(char **split_cmd)
{
	int i;
	t_command *command;

	i = 0;
	command = set_command(split_cmd, &i); // free split_cmd when you done
	while (split_cmd && split_cmd[i])
	{
		i++;
		add_back(command, set_command(split_cmd, &i));
	}
	return (command);
}

void quote_skip(char *str, int *index, char **tmp, char quote)
{
	int start;

	(*index)++;
	start = *index;
	while (str[*index] && str[*index] != quote)
		(*index)++;
	free(*tmp);
	*tmp = ft_substr(str, start, (*index)++ - start);
}

char *filtre_quote(char *str)
{
	int i;
	int start;
	char *tmp;
	char *tmp1;
	char *str_filter;

	str_filter = NULL;
	tmp = NULL;
	i = 0;
	while (str && str[i])
	{
		if (str[i] == '\'')
			quote_skip(str, &i, &tmp, '\'');
		else if (str[i] == '"')
			quote_skip(str, &i, &tmp, '"');
		else
		{
			start = i;
			while (str[i] && str[i] != '\'' && str[i] != '"')
				i++;
			free(tmp);
			tmp = ft_substr(str, start, i - start);
			printf("\e[31mtmp:|%s|\e[0m\n", tmp);
		}
		tmp1 = str_filter;
		str_filter = ft_strjoin(str_filter, tmp);
		free(tmp1);
	}
	return (str_filter);
}

char **append_array(char **old_array, char *arg)
{
	int size;
	char **new_array;

	size = 0;
	if (arg == NULL)
		return (old_array);
	while (old_array && old_array[size])
		size++;
	new_array = malloc(sizeof(char *) * (size + 2));
	if (new_array == NULL)
		return (NULL);
	if (old_array == NULL)
	{
		new_array[0] = ft_strdup(arg);
		new_array[1] = NULL;
		return (new_array);
	}
	size = 0;
	while (old_array[size])
	{
		new_array[size] = ft_strdup(old_array[size]);
		size++;
	}
	free(old_array);
	new_array[size++] = ft_strdup(arg);
	new_array[size] = NULL;
	return (new_array);
}
