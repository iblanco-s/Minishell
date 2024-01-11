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

/******* PARSE_QUOTES *******/
int     closed_quotes(char *str);
char    *is_quote(char *str);
char    *search_quotes(char *st, char c);

/******* PARSE PIPES ********/
int check_pipes(char *str);
int first(char *str);
int last(char *str);
int alone(char *str);

/******* PARSE MYMN *********/
int check_mymn(char *str);
int alone(char *str);
int last(char *str);

/******* PARRSE CHARS *******/
int forbidden_chars(char *str);
int special_char(char *str,char c);
int search_char(char *str,char c);

/******** IS VALID **********/
int input_handler(char *input);
int is_valid(char *str);

/******** SIGNALS ***********/
void        signal_waiting(int i);
static void signal_handler(int signal);
static void child_handler(int signal);

#endif