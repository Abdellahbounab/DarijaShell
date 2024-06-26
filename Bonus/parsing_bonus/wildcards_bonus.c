/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achakkaf <achakkaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 10:54:21 by achakkaf          #+#    #+#             */
/*   Updated: 2024/06/25 12:32:02 by achakkaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_bonus.h"

/*
• find all the maches files name
• sort them by name
*/

char **get_files(void)
{
    DIR *dir;
    struct dirent *file;
    char **filenames;

    dir = opendir(".");
    if (dir == NULL)
        return (NULL);
    file =  readdir(dir);
    while(file)
    {
        filenames = append_array(filenames, file->d_name);
        file =  readdir(dir);
    }
    return (filenames);
}


