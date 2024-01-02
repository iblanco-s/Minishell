/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iblanco- <iblanco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 16:38:51 by iblanco-          #+#    #+#             */
/*   Updated: 2024/01/02 18:39:41 by iblanco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdarg.h>
# include <assert.h>
# include "../libft/libft.h"

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_cmds
{
	char			**opts;
	t_env			*env;
}	t_cmds;

//BUILTINS
int		ft_pwd(void);
char	*ft_strndup(const char *s, size_t n);
void	ft_lstadd_back(t_env **lst, t_env *new);
int		ft_strcmp(const char *str1, const char *str2);
int		ft_unset(t_cmds *cmds);
int		ft_export(t_cmds *cmds);
int		ft_env(t_cmds *cmds);
int		check_alpha_env(t_cmds *cmds, char *str, char *name_command);
int		ft_echo(t_cmds *cmds);
int		ft_exit(t_cmds *cmds);
int		change_env_value(t_cmds *cmds, char *name_env, char *value_env);
int		ft_cd(t_cmds *cmds);
char	*get_env_value(t_cmds *cmds, char *name);
int		change_pwd_and_oldpwd(t_cmds *cmds);
int		go_to_path(t_cmds *cmds, char *path);

//INITIATION


#endif
