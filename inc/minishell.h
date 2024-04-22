/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsalaber <jsalaber@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 16:38:51 by iblanco-          #+#    #+#             */
/*   Updated: 2024/04/22 13:48:35 by jsalaber         ###   ########.fr       */
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
	char			**infile;
	char			**outfile;
	int				*infile_fd;
	int				*outfile_fd;
	char			*eof;
	int				write_mode;
	struct s_cmds	*next;
}	t_cmds;

typedef struct s_shell
{
	t_cmds			*cmds;
	t_env			*env;
}	t_shell;

extern long long	g_exit_status;

// BUILTINS
int		ft_pwd(void);
int		ft_unset(t_shell *shell);
int		ft_export(t_shell *shell);
int		ft_env(t_shell *shell);
int		ft_echo(t_shell *shell);
int		ft_exit(t_shell *shell);
int		ft_cd(t_shell *shell);
int		ft_is_builtin(t_shell *shell);
int		exec_builtin(t_shell *shell);
void	exec_single_builtin(t_shell *shell);

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
void	check_join_quotes_because_special_chars(t_parse *token_list);
void	delete_empty_nodes(t_parse **token_list);
// int		in_redir_type(char *node);
// int		out_redir_type(char *node);
// char	infile_name(char *node);
// char	outfile_name(char *node);

// GROUP BY PIPES
void	group_by_pipes_and_redirs(t_shell *shell, t_parse **token_list);
void	debugg_print_cmds(t_cmds *current_cmd);
char	**list_to_array(t_env *token_list);
int		ft_lstsize_tenv(t_env *lst);
t_cmds	*create_new_cmds_node(void);
void	free_list_parse(t_parse *list);

// AUX REDDIRECTIONS
void	set_output_redirection(t_cmds *cmd, t_parse **current, int fd_type);
void	set_input_redirection(t_cmds *cmd, t_parse **current, int fd_type);
char	**append_to_files_array(char **files, char *new_file);
int		*append_to_reddir_type_array(int *reddir_types, int new_reddir_type);

// EXEC
void	heredoc(char *delimiter);
int		open_infile(char **file, int *infile_fd);
void	create_outfile(char **file);
int		outfile_type(char **file, int *outfile_fd);
void	manage_outfile(t_shell *shell, int *next_pipe);
void	manage_infile(t_shell *shell, int *prev_pipe);
void	ft_error(t_shell *shell, char *error_msg, int exit_status);
void	dup_close_fd(int pipe_fd[2], int fd);
void	start_pipe(t_shell *shell, int pipe_fd[2], int next_pipe[2], t_cmds *node);
void	exec_pipe(t_shell *shell, t_cmds *node);
void	manage_redir(t_shell *shell, int *in_copy, int *out_copy);
char	*ft_get_path(char *path, char *cmd);
void	ft_free_split(char **arr);
void	exec_cmd(t_shell *shell, char **cmd);
void	manage_exec(t_shell *shell);

// MAIN
void	free_general(t_shell *shell);

#endif
