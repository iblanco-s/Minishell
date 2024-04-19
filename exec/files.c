/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junesalaberria <junesalaberria@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 09:40:05 by junesalaber       #+#    #+#             */
/*   Updated: 2024/04/19 15:55:59 by junesalaber      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	manage_outfile(t_cmds *node, int *next_pipe)
{
	int	pipe_fd[2];
	
	if 	(node->outfile)
	{
		create_outfile(node->outfile);
		next_pipe[STDOUT_FILENO] = outfile_type(node->outfile, &node->outfile_fd);
	}
	else if (!node->next)
		next_pipe[STDOUT_FILENO] = outfile_type(node->outfile, &node->outfile_fd);
	if (node->next)
	{
		pipe(pipe_fd);
		{
			if (pipe_fd[1] == -1)
				ft_error(NULL, PIPE_ERROR, EXIT_FAILURE);
		}
	}
}

void	manage_infile(t_cmds *node, int *prev_pipe)
{
	if (node->infile)
		prev_pipe[STDIN_FILENO] = open_infile(node->infile, &node->infile_fd);
}
