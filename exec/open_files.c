/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junesalaberria <junesalaberria@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 10:52:21 by junesalaber       #+#    #+#             */
/*   Updated: 2024/04/11 11:14:23 by junesalaber      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	heredoc(char *delimiter)
{
	
}

int	open_infile(char *file)
{
	int	fd_in;
	
	int	redir_type;
	char *node;

	// esto deberia entrar como parametro a la hora de hacer el parseo
		redir_type = in_redir_type(node);
	if (!*file)
		return (STDIN_FILENO);
	if (redir_type == 2)
		//heredoc
	else
	{
		if (access(file, F_OK) != 0)
			ft_putendl_fd("File does not exist", 2);
		if (access(file, R_OK) != 0)
			ft_putendl_fd("Read error", 2);
		fd_in = open(file, O_RDONLY, 0444);
	}
	if (fd_in == -1)
		ft_putendl_fd("Errpr opening file", 2);
	return (fd_in);	
}
