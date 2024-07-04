/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excution.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abounab <abounab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 18:22:03 by abounab           #+#    #+#             */
/*   Updated: 2024/06/29 19:00:08 by abounab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXCUTION_H
#define EXCUTION_H

#include "../types.h"
#include "../parsing/parsing.h"
#include "../env/env.h"
#include "../getnextline/get_next_line_bonus.h"

int	ft_signals(int child);

int	excution(t_cmd *command, t_env **env);

int	ft_perror(char *header, char *msg, int err);

#endif