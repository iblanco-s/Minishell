/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsalaber <jsalaber@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 09:11:19 by jsalaber          #+#    #+#             */
/*   Updated: 2024/04/22 18:31:17 by jsalaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

long long	g_exit_status = 0;

void	ft_error(t_shell *shell, char *error_msg, int exit_status)
{
	if (shell)
		free_general(shell);
	ft_putendl_fd(error_msg, 2);
	exit(exit_status);
}

void	dup_close_fd(int pipe_fd[2], int fd)
{
	if (pipe_fd[fd] != fd)
		dup2(pipe_fd[fd], fd);
	if (fd == STDIN_FILENO)
		close(pipe_fd[1]);
	else if (fd == STDOUT_FILENO)
		close(pipe_fd[0]);
}

void	start_pipe(t_shell *shell, int pipe_fd[2], int n_pipe[2], t_cmds *node)
{
	pid_t	fork_pid;
	char	*path_val;

	fork_pid = fork();
	if (fork_pid == -1)
		ft_error(shell, FORK_ERROR, EXIT_FAILURE);
	if (fork_pid == 0)
	{
		dup_close_fd(pipe_fd, STDIN_FILENO);
		dup_close_fd(n_pipe, STDOUT_FILENO);
		path_val = path_value(shell);
		exec_cmd(shell, node->opts, path_val);
	}
	if (pipe_fd[0] != STDIN_FILENO)
	{
		close(pipe_fd[0]);
		close(pipe_fd[1]);
	}
	if (n_pipe[STDOUT_FILENO] != STDOUT_FILENO)
		close (n_pipe[STDOUT_FILENO]);
}

void	exec_pipe(t_shell *shell, t_cmds *node)
{
	int		tmp_status;
	int		pipe_fd[2];
	int		next_pipe[2];

	if (pipe(pipe_fd) == -1)
		ft_error(shell, PIPE_ERROR, EXIT_FAILURE); //aqui sueltas error pero seguiria la ejecucion no sale 
	while (node)
	{
		pipe(next_pipe);
		manage_outfile(shell, next_pipe);
		manage_infile(shell, pipe_fd);
		if (!node->opts || !node->opts[0])
			exit (0); //aqui peta si metes solo infile o outfile porque no hay comando y opts esta vacio,
			// el exit es temporal NECESITAMOS ALGUNA FUNCION QUE HAGA DE EXIT DE LA EJECUCION DE UN INPUT Y VUELVA A SACAR EL PROMPT SIN TENER QUE PASAR POR TODA LA EJECUCION, 
			//pregunta como lo hace el resto porque bash lo haze raro, <a lo trata de una forma y >a de otro pero ambas son validas para bash
		start_pipe(shell, pipe_fd, next_pipe, node);
		pipe_fd[STDIN_FILENO] = next_pipe[STDIN_FILENO];
		node = node->next;
	}
	close(pipe_fd[STDIN_FILENO]);
	unlink("/tmp/here_doc");
	while (waitpid(-1, &tmp_status, 0) > 0)
		;
	g_exit_status = tmp_status >> 8;
}
