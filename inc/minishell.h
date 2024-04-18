/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsalaber <jsalaber@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 16:38:51 by iblanco-          #+#    #+#             */
/*   Updated: 2024/04/16 23:37:20 by inigo            ###   ########.fr       */
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
# include <fcntl.h>
# include "../libft/libft.h"

# define ERROR 
# define SUCCESS 
# define EXIT_FAILURE 1

// ERRORS
# define ERROR_MANY_ARGS "minishell: init: too many arguments"
# define PIPE_ERROR "minishell: pipe() failed"
# define FORK_ERROR "minishell: fork() failed"

// ESTRUCTURA PARA PARSEO
typedef struct s_parse
{
	char			*token;
	int				quote;
	int				join_with_quotes;
	struct s_parse	*next;
}	t_parse;

// ESTRUCTURA DE VARIABLES DE ENTORNO
// NAME: NOMBRE DE LA VARIABLE Y VALUE: VALOR DE LA VARIABLE
typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_cmds
{
	char			**opts;
	t_env			*aux_list_parse;
	//flags int red;
	char			*infile;
	char			*outfile;
	int				infile_fd;
	int				outfile_fd;
	char			*eof;
	int				write_mode;
	struct s_cmds	*next;
}	t_cmds;

typedef struct s_shell
{
	t_cmds			cmds;
	t_env			*env; //-> enviroments
}	t_shell;

extern	long long g_exit_status;

// BUILTINS
int		ft_pwd(void);
int ft_unset(t_shell *shell);
int ft_export(t_shell *shell);
int ft_env(t_shell *shell);
int ft_echo(t_shell *shell);
int ft_exit(t_shell *shell);
int ft_cd(t_shell *shell);

// BUILTINS UTILS
char	*ft_strndup(const char *s, size_t n);
void	ft_lstadd_back(t_env **lst, t_env *new);
t_env	*ft_lstlast(t_env *lst);
int		ft_strcmp(const char *str1, const char *str2);
int		check_alpha_env(t_cmds *cmds, char *str, char *name_command);
int		change_env_value(t_shell *shell, char *name_env, char *value_env);
char	*get_env_value(t_shell *shell, char *name);
int		change_pwd_and_oldpwd(t_shell *shell);
int		go_to_path(t_shell *shell, char *path);

// INITIATION
t_env	*env_to_list(char **env);
t_shell	*setup_program(char **env);

// PARSE
void	handle_input(char *line, t_shell *shell);
t_parse	*general_split(char *line, t_shell *shell);
void	split_dollar(t_parse *tokens_list, t_shell *shell);
void	divide_str_by_char(t_env *token_list, int i);
void	check_pipes_and_redirs(t_parse *token_list);
char	**list_to_array(t_env *token_list);
void	join_nodes_because_quotes(t_parse **token_list);
int		ft_lstsize_parse(t_parse *lst);
t_parse	*ft_lstlast_parse(t_parse *lst);
void	ft_lstadd_back_parse(t_parse **lst, t_parse *new);
// int		in_redir_type(char *node);
// int		out_redir_type(char *node);
// char	infile_name(char *node);
// char	outfile_name(char *node);

// GROUP BY PIPES
void	group_by_pipes_and_redirs(t_shell *shell, t_parse **token_list);

// EXEC
void	heredoc(char *delimiter);
int		open_infile(char *file);
int		outfile_type(char *file);
void	ft_error(t_shell *shell, char *error_msg, int exit_status);
void	dup_close_fd(int pipe_fd[2], int fd);
void	start_pipe(t_shell *shell);

// MAIN
void	free_general(t_shell *shell);

#endif
