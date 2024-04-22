/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsalaber <jsalaber@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 09:40:05 by junesalaber       #+#    #+#             */
/*   Updated: 2024/04/22 18:16:59 by jsalaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	manage_outfile(t_shell *shell, int *next_pipe)
{
	int		pipe_fd[2];
	t_cmds	*node;

	node = shell->cmds;
	if (node->outfile)
	{
		create_outfile(node->outfile);
		next_pipe[STDOUT_FILENO]
			= outfile_type(node->outfile, node->outfile_fd);
	}
	else if (!node->next)
		next_pipe[STDOUT_FILENO]
			= outfile_type(node->outfile, node->outfile_fd);
	if (node->next)
	{
		pipe(pipe_fd);
		{
			if (pipe_fd[1] == -1)
				ft_error(NULL, PIPE_ERROR, EXIT_FAILURE);
		}
	}
}

void	manage_infile(t_shell *shell, int *prev_pipe)
{
	t_cmds	*node;

	node = shell->cmds;
	if (node->infile)
		prev_pipe[STDIN_FILENO] = open_infile(node->infile, node->infile_fd);
}
