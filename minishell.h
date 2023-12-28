/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghoyuelo <ghoyuelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 14:34:46 by ghoyuelo          #+#    #+#             */
/*   Updated: 2023/11/29 14:34:46 by ghoyuelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h> //printf,
#include <stdlib.h> //exit,

typedef struct s_data
{
    char    *mini_env;
}   t_data;

/******* PARSE_QUOTES ********/
int	closed_quotes(char *str);

/******* PARSE PIPES *******/

#endif