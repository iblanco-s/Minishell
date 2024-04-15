/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsalaber <jsalaber@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 10:52:21 by junesalaber       #+#    #+#             */
/*   Updated: 2024/04/15 09:41:05 by jsalaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	heredoc(char *delimiter)
{
	char	*line;
	int		doc_file;

	doc_file = open("/tmp/here_doc", O_CREAT | O_RDWR | O_TRUNC);
	write(1, "< ", 2);
	line = get_next_line(STDIN_FILENO);
	if (!line)
	{
		close(doc_file);
		return ;
	}
	while (ft_strncmp(line, delimiter, ft_strlen(line) - 1))
	{
		write(doc_file, line, ft_strlen(line));
		free (line);
		write(1, "> ", 2);
		line = get_next_line(STDIN_FILENO);
		if (!line)
			break ;
	}
	free (line);
	close (doc_file);
}

int	open_infile(char *file)
{
	int		fd_in;
	int		redir_type;
	char	*node;

	// esto deberia entrar como parametro a la hora de hacer el parseo
		redir_type = in_redir_type(node);
	if (!*file)
		return (STDIN_FILENO);
	if (redir_type == 2)
	{
		heredoc(file);
		fd_in = open("/tmp/here_doc", O_RDONLY, 0444);
	}
	else
	{
		if (access(file, F_OK) != 0)
			ft_putendl_fd("File does not exist", 2);
		if (access(file, R_OK) != 0)
			ft_putendl_fd("Read error", 2);
		fd_in = open(file, O_RDONLY, 0444);
	}
	if (fd_in == -1)
		ft_putendl_fd("Error opening file", 2);
	return (fd_in);
}

int	outfile_type(char *file)
{
	int		fd_out;
	int		redir_type;
	char	*node;
	int		mode;
	// esto deberia entrar como parametro a la hora de hacer el parseo
	redir_type = out_redir_type(node);
	if (!file)
		return (STDOUT_FILENO);
	if (redir_type == 1)
		mode = O_TRUNC;
	else
		mode = O_APPEND;
	if (access(file, F_OK) != 0)
	{
		fd_out = open(file, O_CREAT | O_WRONLY | mode, 0644);
		if (fd_out == -1)
			ft_putendl_fd("Outfile error", 2);
	}
	else
	{
		fd_out = open (file, O_WRONLY | mode, 0644);
		if (fd_out == -1)
			ft_putendl_fd("Outfile error", 2);
	}
	return (fd_out);
}
