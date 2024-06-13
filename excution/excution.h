/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excution.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abounab <abounab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 18:22:03 by abounab           #+#    #+#             */
/*   Updated: 2024/06/13 19:10:17 by abounab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXCUTION_H
#define EXCUTION_H

#include "../types.h"
#include "../env/env.h"
#include "../getnextline/get_next_line_bonus.h"

int	excution(t_cmd *command, t_env *env, int *status);

#endif