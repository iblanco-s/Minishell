/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsalaber <jsalaber@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 09:11:19 by jsalaber          #+#    #+#             */
/*   Updated: 2024/04/18 12:13:26 by jsalaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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

void	start_pipe(t_shell *shell)
{
	pid_t	fork_pid;
	int		pipe_fd[2];

	if (pipe(pipe_fd) == -1)
		ft_error(shell, PIPE_ERROR, EXIT_FAILURE);
	fork_pid = fork();
	if (fork_pid == -1)
		ft_error(shell, FORK_ERROR, EXIT_FAILURE);
	if (fork_pid == 0)
	{
		dup_close_fd(pipe_fd[0], STDIN_FILENO);
		dup_close_fd(pipe_fd[1], STDOUT_FILENO);
		//exec_cmd(shell);
	}
	close(pipe_fd[0]);
	close(pipe_fd[1]);
}

void	exec_pipe(t_shell *shell)
{
	int		tmp_status;

	waitpid(fork_pid, &tmp_status, 0);
	g_exit_status = tmp_status >> 8;
}