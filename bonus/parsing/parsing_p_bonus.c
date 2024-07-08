/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_p_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achakkaf <achakkaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 10:13:51 by achakkaf          #+#    #+#             */
/*   Updated: 2024/07/08 12:50:06 by achakkaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_bonus.h"

/*

(.. || .. && ( .. &&  .. ) | .. && .. ) | .. && (.. && ..) | ..

*/

int	bonus_addback(t_bonus **lst, t_bonus *newnode)
{
	t_bonus *cpy;

	cpy = *lst;
	if (lst)
	{
		if (!*lst)
			*lst = newnode;
		else
		{
			while (cpy && cpy->next)
				cpy = cpy->next;
			cpy->next = newnode;
		}
		return 1;
	}
	return 0;
}


char *join_array(char **array)
{
	int i;
	char *tmp;
	char *string;

	i = 0;
	string = NULL;
	while (array && array[i])
	{
		tmp = string;
		string = ft_strjoin(string, array[i]);
		free(tmp);
		if (array[i + 1])
		{
			tmp = string;
			string = ft_strjoin(string, " ");
			free(tmp);
		}
		i++;
	}
	return (string);
}

int check_paro(char **array)
{
	int i;
	int open_count;

	open_count = 0;
	i = 0;
	while (array && array[i])
	{
		if (array[i][0] == '(')
			open_count++;
		else if (array[i][0] == ')')
		{
			if (open_count == 0)
				return ERROR;
			// if (array[i + 1][0] != '|' || array[i + 1][0] != '&' || array[i + 1][0] != '<')
			open_count--;
		}
		i++;
	}
	if (open_count != 0)
		return (ERROR);
	return (GOOD);
}

int check_f_l(char **array)
{
	int i;
	int open_count;

	open_count = 0;
	i = 0;
	while (array && array[i])
	{
		if (array[i][0] == '(')
			open_count++;
		else if (array[i][0] == ')')
		{
			open_count--;
			if (open_count == 0 && array[i + 1] == NULL)
				return (GOOD);
			if (open_count == 0 && array[i + 1] != NULL)
				return (ERROR);
		}
		i++;
	}
	return (ERROR);
}

// remove first and last element from an array
char **remove_f_l(char **array)
{
	int i;
	char **new_array;

	new_array = NULL;
	i = 1;
	while (array && array[i + 1])
	{
		new_array = append_array(new_array, array[i]);
		i++;
	}
	return (new_array);
}

// (.. || .. && ( .. && .. ) | .. && .. ) | .. && (.. && ..) | .. < ..

//	bonus->cmdline;		this rest of command
// 	bonus->relation;	relation between those commands
// 	bonus->command;		simple command
// 	bonus->next_bonus;	complex command

// bonus->command:
// bonus->args;
// bonus->status;
// bonus->files;
// bonus->next_pipe;
// bonus->bonus;

bool is_operator(const char *str)
{
	return (strcmp(str, "&&") == 0 || strcmp(str, "||") == 0);
}

int skip_p(char **array, int index)
{
	int i;
	int open_count;

	i = index;
	open_count = 0;
	while (array[i] != NULL)
	{
		if (array[i][0] == '(')
			open_count++;
		else if (array[i][0] == ')')
		{
			if (open_count == 0)
				return (i);
			open_count--;
		}
		if (open_count == 0)
			return (i);
		i++;
	}
	return (i);
}

int skip_and_or(char **array, int index)
{
	int i;
	int open_count;

	i = index;
	open_count = 0;
	while (array[i] != NULL)
	{
		if (strcmp(array[i], "(") == 0)
			open_count++;
		else if (strcmp(array[i], ")") == 0)
			open_count--;
		if (open_count == 0 && is_operator(array[i]))
			return i;
		i++;
	}
	return (i);
}

// (.. || .. && ( .. && .. ) | .. && .. ) | .. && (.. && ..) | .. < ..

char **sub_split(char **array, int start, int end)
{
	char **sub_array;

	sub_array = NULL;
	while (array && start < end)
	{
		sub_array = append_array(sub_array, array[start]);
		start++;
	}
	return (sub_array);
}

t_bonus *ft_bonussplit(t_bonus *bonus)
{
	int i;
	int cpy;
	t_bonus *head;
	t_bonus *cpy_bonus;

	i = 0;
	head = NULL;
	if (bonus == NULL)
		return (NULL);
	while (bonus->cmdline && bonus->cmdline[i])
	{
		cpy = i;
		i = skip_and_or(bonus->cmdline, i);
		if (!bonus->cmdline[i] || (!ft_strcmp(bonus->cmdline[i], "||") || !ft_strcmp(bonus->cmdline[i], "&&")))
		{
			// bonus->command->bonus->cmdline = sub_split(bonus->cmdline, cpy, i);
			// ihave to malloc for command too
			cpy_bonus = create_bonus(sub_split(bonus->cmdline, cpy, i));
			if (!bonus->cmdline[i])
				cpy_bonus->relation = NONE;
			else if (!ft_strcmp(bonus->cmdline[i], "||"))
				cpy_bonus->relation = OR;
			else 
				cpy_bonus->relation = AND;
			bonus_addback(&head, cpy_bonus);
			// bonus->command->bonus->cmdline
		}
		if (bonus->cmdline[i] ==  NULL)
			break;
		// bonus->command->files
		i++;
	}
	return (head);
}

int skip_s(char **array, int index, char *s1)
{
	int i;
	int open_count;

	i = index;
	open_count = 0;
	while (array[i] != NULL)
	{
		if (strcmp(array[i], "(") == 0)
			open_count++;
		else if (strcmp(array[i], ")") == 0)
			open_count--;
		if (open_count == 0 && !ft_strcmp(array[i], s1))
			return i;
		i++;
	}
	return (i);
}

int is_simple_command(char **cmdline)
{
	int i;

	i = 0;
	while (cmdline && cmdline[i])
	{
		if (is_operator(cmdline[i]) || !ft_strcmp(cmdline[i], "(") || !ft_strcmp(cmdline[i], ")"))
			return (ERROR);
		i++;
	}
	return (GOOD);
}
