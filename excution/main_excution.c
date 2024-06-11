/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_excution.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abounab <abounab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 18:21:23 by abounab           #+#    #+#             */
/*   Updated: 2024/06/11 19:17:01 by abounab          ###   ########.fr       */
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
*/


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
	while 
}
