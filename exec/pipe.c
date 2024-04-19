/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junesalaberria <junesalaberria@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 09:11:19 by jsalaber          #+#    #+#             */
/*   Updated: 2024/04/19 16:43:11 by junesalaber      ###   ########.fr       */
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

void	start_pipe(t_shell *shell, int pipe_fd[2], int next_pipe[2])
{
	pid_t	fork_pid;

	fork_pid = fork();
	if (fork_pid == -1)
		ft_error(shell, FORK_ERROR, EXIT_FAILURE);
	if (fork_pid == 0)
	{
		dup_close_fd(pipe_fd, STDIN_FILENO);
		dup_close_fd(next_pipe, STDOUT_FILENO);
		//exec_cmd(shell);
	}
	if (pipe_fd[0] != STDIN_FILENO)
	{
		close(pipe_fd[0]);
		close(pipe_fd[1]);
	}
	if (next_pipe[STDOUT_FILENO] != STDOUT_FILENO)
		close (next_pipe[STDOUT_FILENO]);
}

void	exec_pipe(t_shell *shell, t_cmds *node)
{
	int		tmp_status;
	int		pipe_fd[2];
	int		next_pipe[2];

	if (pipe(pipe_fd) == -1)
		ft_error(shell, PIPE_ERROR, EXIT_FAILURE);
	while (node)
	{
		pipe(next_pipe);
		manage_outfile(node, next_pipe);
		manage_infile(node, pipe_fd);
		start_pipe(shell, pipe_fd, next_pipe);
		pipe_fd[STDIN_FILENO] = next_pipe[STDIN_FILENO];
		node = node->next;
	}
	close(pipe_fd[STDIN_FILENO]);
	unlink("/tmp/here_doc");
	while (waitpid(-1, &tmp_status, 0) > 0)
		;
	g_exit_status = tmp_status >> 8;
}
