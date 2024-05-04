/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsalaber <jsalaber@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 09:11:19 by jsalaber          #+#    #+#             */
/*   Updated: 2024/04/30 18:23:59 by jsalaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	dup_close_fd(int pipe_fd[2], int fd)
{
	if (pipe_fd[fd] != fd)
	{
		dup2(pipe_fd[fd], fd);
		close(pipe_fd[1]);
		close(pipe_fd[0]);
	}
}

void	child_fun(t_shell *shell, int pipe_fd[2], int n_pipe[2], t_cmds *node)
{
	char	*path_val;
	char	**tmp_envp;

	dup_close_fd(pipe_fd, STDIN_FILENO);
	dup_close_fd(n_pipe, STDOUT_FILENO);
	path_val = path_value(shell);
	tmp_envp = env_to_envp(shell->env);
	exec_cmd(shell, node->opts, path_val, tmp_envp);
	ft_free_array(tmp_envp);
	free(path_val);
}

void	start_pipe(t_shell *shell, int pipe_fd[2], int n_pipe[2], t_cmds *node)
{
	pid_t	fork_pid;

	if (!shell->cmds->opts || !shell->cmds->opts[0])
		return ;
	fork_pid = fork();
	if (fork_pid == -1)
		ft_error(shell, FORK_ERROR, EXIT_FAILURE);
	if (fork_pid == 0)
	{
		child_fun(shell, pipe_fd, n_pipe, node);
	}
	if (pipe_fd[0] != STDIN_FILENO)
	{
		close(pipe_fd[0]);
		close(pipe_fd[1]);
	}
	if (n_pipe[STDOUT_FILENO] != STDOUT_FILENO)
		close (n_pipe[STDOUT_FILENO]);
}

void	exec_pipe(t_shell *shell, t_cmds *node, t_cmds *head_node)
{
	int		tmp_status;
	int		pipe_fd[2];
	int		next_pipe[2];

	ft_pipe(pipe_fd);
	tmp_status = 0;
	while (node)
	{
		ft_pipe(next_pipe);
		if (manage_infile(node, pipe_fd, head_node) == -1)
			break ;
		manage_outfile(node, next_pipe);
		if (!node->opts || !node->opts[0])
			ft_continue_error(COMMAND_ERROR);
		if (pipe_fd[STDIN_FILENO] >= 0)
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
