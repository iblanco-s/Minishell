/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iblanco- <iblanco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 09:40:05 by junesalaber       #+#    #+#             */
/*   Updated: 2024/04/24 18:21:54 by iblanco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	manage_outfile(t_cmds *node, int *next_pipe)
{
	int		pipe_fd[2];

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
		if (pipe(pipe_fd) == -1)
			ft_error(NULL, PIPE_ERROR, EXIT_FAILURE);
	}
}

int	manage_infile(t_cmds *node, int *prev_pipe, t_cmds *head)
{
	if (node->infile || node == head)
	{
		prev_pipe[STDIN_FILENO] = open_infile(node->infile, node->infile_fd);
		if (prev_pipe[STDIN_FILENO] == -1)
			return (-1);
	}
	return (0);
}
