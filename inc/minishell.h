/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inigo <inigo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 16:38:51 by iblanco-          #+#    #+#             */
/*   Updated: 2024/04/05 18:24:03 by inigo            ###   ########.fr       */
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
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/ioctl.h>
# include <signal.h>
# include "../libft/libft.h"

# define ERROR 
# define SUCCESS 
# define EXIT_FAILURE 1

// ERRORS
# define ERROR_MANY_ARGS "minishell: init: too many arguments"

// ESTRUCTURA DE VARIABLES DE ENTORNO
// NAME: NOMBRE DE LA VARIABLE Y VALUE: VALOR DE LA VARIABLE
// PERO TAMBIEN SE HA USADO EN EL PARSEO PARA GUARDAR LOS TOKENS
// NAME: NOMBRE DEL TOKEN, VALUE: NULL Y SINGLE_QUOTE: PARA SABER SI
// EL TOKEN ESTA EN COMILLAS SIMPLES Y NO SE DEBE EXPANDIR
typedef struct s_env
{
	char			*name;
	char			*value;
	int				single_quote;
	int				join_with_quotes;
	struct s_env	*next;
}	t_env;

// ESTRUCTURA GENERAL: 
// LA IDEA INICIAL ERA QUE CADA
// COMANDO TUVIERA SU PROPIA ESTRUCTURA, 
// EJ: ECHO "HOLA" "ADIOS" SERIA UNA ESTRUCTURA, OPTS = [ECHO, "HOLA", "ADIOS"]
// Y ENV = [VARIABLES DE ENTORNO]
// PERO SEGURAMENTE TENGAMOS QUE CAMBIAR ESTO, Y POR LO TANTO TAMBIEN
// CAMBIAR LA FORMA DE PASAR LOS PARAMETROS A LOS BUILTINS
typedef struct s_cmds
{
	char			**opts;
	t_env			*env;
}	t_cmds;

// BUILTINS
int		ft_pwd(void);
int		ft_unset(t_cmds *cmds);
int		ft_export(t_cmds *cmds);
int		ft_env(t_cmds *cmds);
int		ft_echo(t_cmds *cmds);
int		ft_exit(t_cmds *cmds);
int		ft_cd(t_cmds *cmds);

// BUILTINS UTILS
char	*ft_strndup(const char *s, size_t n);
void	ft_lstadd_back(t_env **lst, t_env *new);
t_env	*ft_lstlast(t_env *lst);
int		ft_strcmp(const char *str1, const char *str2);
int		check_alpha_env(t_cmds *cmds, char *str, char *name_command);
int		change_env_value(t_cmds *cmds, char *name_env, char *value_env);
char	*get_env_value(t_cmds *cmds, char *name);
int		change_pwd_and_oldpwd(t_cmds *cmds);
int		go_to_path(t_cmds *cmds, char *path);

// INITIATION
t_env	*env_to_list(char **env);
t_cmds	*setup_program(char **env);

// PARSE
void	handle_input(char *line, t_cmds *cmds);
t_env	*general_split(char *line, t_cmds *cmds);
void	split_dollar(t_env *tokens_list, t_cmds *cmds);
void	divide_str_by_char(t_env *token_list, int i);
void	check_pipes_and_redirs(t_env *token_list);
char	**list_to_array(t_env *token_list);
void	join_nodes_because_quotes(t_env **token_list);

// GROUP BY PIPES
void	group_by_pipes(t_env **token_list);

// MAIN
void	free_general(t_cmds *cmds);

#endif
