/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsalaber <jsalaber@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 10:52:21 by junesalaber       #+#    #+#             */
/*   Updated: 2024/04/29 18:53:25 by jsalaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	heredoc(char *delimiter)
{
	char	*line;
	int		doc_file;

	doc_file = open("/tmp/here_doc", O_CREAT | O_RDWR | O_TRUNC);
	write(1, "> ", 2);
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

int	open_infile(char **file, int *infile_fd)
{
	int		fd_in;

	if (!file || !*file)
		return (STDIN_FILENO);
	while (*file != NULL)
	{
		if (*infile_fd == 2)
		{
			heredoc(*file);
			fd_in = open("/tmp/here_doc", O_RDONLY, 0444);
		}
		if (*infile_fd == 1 && access(*file, F_OK) != 0)
			return (ft_continue_error(FILE_ERROR), -1);
		else if (*infile_fd == 1 && access(*file, R_OK) != 0)
			return (ft_putendl_fd("Read error", 2), -1);
		else if (*infile_fd == 1 && *(file + 1) == NULL)
		{
			fd_in = open(*file, O_RDONLY, 0444);
			if (fd_in == -1)
				return (ft_putendl_fd("Error opening file", 2), -1);
		}
		file ++;
		infile_fd++;
	}
	return (fd_in);
}

void	create_outfile(char **file)
{
	int		fd_out;

	if (!*file)
		return ;
	while (*file)
	{
		if (access(*file, F_OK) != 0)
		{
			fd_out = open(*file, O_CREAT, 0644);
			if (fd_out == -1)
				ft_putendl_fd("Outfile create error", 2);
			close(fd_out);
		}
		file++;
	}
}

int	outfile_type(char **file, int *outfile_fd)
{
	int		fd_out;
	int		write_mode;

	if (!file || !*file)
		return (STDOUT_FILENO);
	fd_out = -1;
	write_mode = 0;
	while (*file)
	{
		if (*(file + 1) == NULL)
		{
			if (*outfile_fd == 2)
				write_mode = O_APPEND;
			else if (*outfile_fd == 1)
				write_mode = O_TRUNC;
			fd_out = open (*file, O_WRONLY | write_mode, 0644);
			if (fd_out == -1)
				ft_putendl_fd("Outfile error", 2);
			break ;
		}
		file++;
		outfile_fd++;
	}
	return (fd_out);
}
