/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iblanco- <iblanco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 16:38:51 by iblanco-          #+#    #+#             */
/*   Updated: 2023/12/15 17:05:07 by iblanco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <assert.h>

typedef struct s_env
{
    char            *name;
    char            *value;
	struct s_env    *next;
} t_env;

typedef struct s_cmds
{
	char			**opts;
	t_env			*env;
} t_cmds;

int		ft_pwd();
char	*ft_strndup(const char *s, size_t n);
char	*ft_strdup(const char *s);
void	ft_lstadd_back(t_env **lst, t_env *new);
int		ft_strcmp(const char *str1, const char *str2);
int		ft_unset(t_cmds *cmds);
int		ft_export(t_cmds *cmds);
int		ft_env(t_cmds *cmds);
int		ft_isalpha(int a);
int		check_alpha_env(t_cmds *cmds ,char *str, char *name_command);
int		ft_echo(t_cmds *cmds);
int		ft_isdigit(int a);
int		ft_atoi(const char *str);
int		ft_exit(t_cmds *cmds);
int		change_env_value(t_cmds *cmds, char *name_env, char *value_env);

#endif