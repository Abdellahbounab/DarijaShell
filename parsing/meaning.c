/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meaning.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achakkaf <achakkaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 11:21:18 by achakkaf          #+#    #+#             */
/*   Updated: 2024/06/02 16:52:09 by achakkaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

// [< , Makefile]                                           ->      filenames[Makefile]
// [<, Makefile, >, output, cat, -e, >, ou ] 				->		filesnames:[Makefile, output, ou], input: Makefile, ouput: ou
// [<, 'Makefile', >, "out"put, cat, -e, >, ou ]			->		filesnames:[Makefile, output, ou], input: Makefile, ouput: ou
// $arg=Make, [<, '$argfile', >, "out"put, cat, -e, >, ou ] ->		filesnames:[Makefile, output, ou], input: Makefile, ouput: ou

// t_cmd *create_cmd(char **line, t_env *env)
// {
// 	t_cmd *cmd;
// 	t_env *tmp_env;
// 	static int i;
// 	int end;
// 	int start;
// 	char *tmp;
// 	char *var;
// 	char *token;
// 	char *tmp_token;
// 	char *tmp_join;

// 	token = NULL;
// 	if (line == NULL)
// 		return (NULL);
// 	cmd = malloc(sizeof(t_cmd));
// 	if (cmd == NULL)
// 		return (NULL);
// 	i = 0;
// 	while (line[i])
// 	{
// 		end = 0;
// 		if (ft_strcmp(line[i], "|") == 0)
// 			i++;
// 		else if (ft_strcmp(line[i], "<") == 0)
// 		{
// 			i++;
// 			while (line[i][end])
// 			{
// 				if (line[i][end] == '\'')
// 				{
// 					end++;
// 					start = end;
// 					while (line[i][end] != '\'')
// 						end++;
// 					tmp = ft_substr(line[i], start, end - start);
// 				}
// 				else if (line[i][end] == '"')
// 				{
// 					end++;
// 					start = end;
// 					// arg=3 : <, 'Make'"fi"le"Number$arg dhel $arg2"
// 					while (line[i][end] != '"')
// 					{
// 						if (line[i][end] != '$')
// 						{
// 							tmp_token = ft_substr(line[i], start, end - start);
// 							end++;
// 							start = end;
// 							while (token[end] && (ft_isalpha(token[end]) == GOOD || ft_isdigit(token[end]) == GOOD || token[end] == '_'))
// 								end++;
// 							var = ft_substr(line[i], start, end - start);
// 							tmp_env = env;
// 							while (tmp_env)
// 							{
// 								if (ft_strcmp(tmp_env->key, var) == GOOD)
// 								{
// 									tmp = ft_strjoin(tmp_token, tmp_env->value);
// 									break;
// 								}
// 								tmp_env = tmp_env->next;
// 							}
// 							free(var);
// 							free(tmp_token);
// 							start = end;
// 						}
// 						else
// 							end++;
// 					}
// 					tmp_token = ft_substr(line[i], start, end - start);
// 					tmp = ft_strjoin(tmp_token, tmp);
// 				}
// 				else
// 				{
// 					start = end;
// 					while (line[i][end] && line[i][end] != '"' && line[i][end] != '\'')
// 					{
// 						f(line[i][end] != '$')
// 						{
// 							tmp_token = ft_substr(line[i], start, end - start);
// 							end++;
// 							start = end;
// 							while (token[end] && (ft_isalpha(token[end]) == GOOD || ft_isdigit(token[end]) == GOOD || token[end] == '_'))
// 								end++;
// 							var = ft_substr(line[i], start, end - start);
// 							tmp_env = env;
// 							while (tmp_env)
// 							{
// 								if (ft_strcmp(tmp_env->key, var) == GOOD)
// 								{
// 									tmp = ft_strjoin(tmp_token, tmp_env->value);
// 									break;
// 								}
// 								tmp_env = tmp_env->next;
// 							}
// 							free(var);
// 							free(tmp_token);
// 							start = end;
// 						}
// 						else end++;
// 					}
// 				}
// 				tmp_join = token;
// 				token = ft_strjoin(token, tmp);
// 				free(tmp);
// 				free(tmp_join);
// 			}
// 		}
// 		// else if (ft_strcmp(line[i], ">") == 0)
// 		// {
// 		// }
// 		// else if (ft_strcmp(line[i], ">>") == 0)
// 		// {
// 		// }
// 		// else if (ft_strcmp(line[i], "<<") == 0)
// 		// {
// 		// }
// 		i++;
// 	}
// }

// char *filtre_quote(char *str)
// {
// 	int i;
// 	int start;
// 	char *tmp;
// 	char *tmp1;
// 	char *str_filter;

// 	str_filter = NULL;
// 	tmp = NULL;
// 	i = 0;
// 	while (str && str[i])
// 	{
// 		if (str[i] == '\'')
// 			quote_skip(str, &i, &tmp, '\'');
// 		else if (str[i] == '"')
// 			quote_skip(str, &i, &tmp, '"');
// 		else
// 		{
// 			start = i;
// 			while (str[i] && str[i] != '\'' && str[i] != '"')
// 				i++;
// 			free(tmp);
// 			tmp = ft_substr(str, start, i - start);
// 			printf("\e[31mtmp:|%s|\e[0m\n", tmp);
// 		}
// 		tmp1 = str_filter;
// 		str_filter = ft_strjoin(str_filter, tmp);
// 		free(tmp1);
// 	}
// 	return (str_filter);
// }

char *filter(char *line, t_env *env)
{
	t_cmd *cmd;
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
					printf("line[end]: %c\n", line[end]);
					tmp_token = ft_substr(line, start, end - start);
					printf("tmp_token: %s\n", tmp_token);
					tmp_all = ft_strjoin(tmp_all, tmp_token);
					printf("tmp_all: %s\n", tmp_all);
					end++;
					start = end;
					while (line[end] && (ft_isalpha(line[end]) == GOOD || ft_isdigit(line[end]) == GOOD || line[end] == '_'))
						end++;
					var = ft_substr(line, start, end - start);
					printf("var: %s\n", var);
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
					// free(var);
					// free(tmp_token);
					start = end;
				}
				else 
					end++;
			}
			tmp_join = ft_substr(line, start, end - start);
			tmp = ft_strjoin(tmp_all, tmp_join);
		}
		else
		{
			start = end;
			while (line[end] && line[end] != '"' && line[end] != '\'')
			{
				if (line[end] == '$')
				{
					// printf("line[end]: %c\n", line[end]);
					tmp_token = ft_substr(line, start, end - start);
					// printf("tmp_token: %s\n", tmp_token);
					end++;
					start = end;
					while (line[end] && (ft_isalpha(line[end]) == GOOD || ft_isdigit(line[end]) == GOOD || line[end] == '_'))
						end++;
					var = ft_substr(line, start, end - start);
					// printf("var: %s\n", var);
					tmp_env = env;
					while (tmp_env)
					{
						// printf("value: %s\n", tmp_env->value);
						if (ft_strcmp(tmp_env->key, var) == GOOD)
						{
							tmp_token = ft_strjoin(tmp_token, tmp_env->value);
							break;
						}
						tmp_env = tmp_env->next;
					}
					tmp_all = ft_strjoin(tmp_all, tmp_token);
					// printf("tmp_all: %s\n", tmp_all);
					// free(var);
					// free(tmp_token);
					start = end;
				}
				else 
					end++;
			}
			tmp_join = ft_substr(line, start, end - start);
			tmp = ft_strjoin(tmp_all, tmp_join);

		}
		// tmp_join = token;
		token = ft_strjoin(token, tmp);
		// free(tmp);
		// free(tmp_join);
	}
	return (token);
}
