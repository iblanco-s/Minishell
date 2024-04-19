/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junesalaberria <junesalaberria@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 10:52:21 by junesalaber       #+#    #+#             */
/*   Updated: 2024/04/19 09:38:41 by junesalaber      ###   ########.fr       */
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

int	open_infile(char *file, int *infile_fd)
{
	int		fd_in;

	if (!*file)
		return (STDIN_FILENO);
	while (*infile_fd)
	{
		if (*infile_fd == 2)
		{
			heredoc(file);
			fd_in = open("/tmp/here_doc", O_RDONLY, 0444);
		}
		else if (*infile_fd == 1)
		{
			if (access(file, F_OK) != 0)
				ft_putendl_fd("File does not exist", 2);
			if (access(file, R_OK) != 0)
				ft_putendl_fd("Read error", 2);
			fd_in = open(file, O_RDONLY, 0444);
		}
		if (fd_in == -1)
			ft_putendl_fd("Error opening file", 2);
		infile_fd++;
	}
	return (fd_in);
}

void	create_outfile(char *file)
{
	int		fd_out;
	
	if (!file)
		return ;
	if (access(file, F_OK) != 0)
	{
		fd_out = open(file, O_CREAT, 0644);
		if (fd_out == -1)
			ft_putendl_fd("Outfile create error", 2);
		close(fd_out);
	}
	
}

int	outfile_type(char *file, int *outfile_fd)
{
	int		fd_out;
	int		write_mode;
	
	if (!file)
		return (STDOUT_FILENO);
	while (outfile_fd)
	{
		if (*outfile_fd == 1)
			write_mode = O_APPEND;
		else if (*outfile_fd == 2)
			write_mode = O_TRUNC;
		fd_out = open (file, O_WRONLY | write_mode, 0644);
		if (fd_out == -1)
			ft_putendl_fd("Outfile error", 2);
		outfile_fd++;
	}
	return (fd_out);
}
