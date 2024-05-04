/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsalaber <jsalaber@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 09:07:32 by jsalaber          #+#    #+#             */
/*   Updated: 2024/04/22 18:36:07 by jsalaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_free_gnl(char **str)
{
	free(*str);
	*str = NULL;
	return (NULL);
}

char	*ft_read_file(int fd, char *saved)
{
	int			readline;
	char		*buffer;

	readline = 1;
	buffer = malloc (sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (ft_free_gnl(&saved));
	buffer[0] = '\0';
	while (readline > 0 && !ft_strchr_gnl(buffer, '\n'))
	{
		readline = read(fd, buffer, BUFFER_SIZE);
		if (readline > 0)
		{
			buffer[readline] = '\0';
			saved = ft_strjoin_gnl(saved, buffer);
		}
	}
	free (buffer);
	if (readline == -1)
		return (ft_free_gnl(&saved));
	return (saved);
}

char	*ft_new_line(char *saved)
{
	char	*line;
	char	*ptr;
	int		len;

	ptr = ft_strchr_gnl(saved, '\n');
	len = (ptr - saved) + 1;
	line = ft_substr_gnl(saved, 0, len);
	if (!line)
		return (NULL);
	return (line);
}

char	*ft_clean_saved(char *saved)
{
	char	*new;
	char	*ptr;
	int		len;

	ptr = ft_strchr_gnl(saved, '\n');
	if (!ptr)
	{
		new = NULL;
		return (ft_free_gnl(&saved));
	}
	else
		len = (ptr - saved) + 1;
	if (!saved[len])
		return (ft_free_gnl(&saved));
	new = ft_substr_gnl(saved, len, ft_strlen_gnl(saved) - len);
	ft_free_gnl(&saved);
	if (!new)
		return (NULL);
	return (new);
}

char	*get_next_line(int fd)
{
	static char	*saved = NULL;
	char		*line;

	if (fd < 0)
		return (NULL);
	if ((saved && !ft_strchr_gnl(saved, '\n')) || !saved)
		saved = ft_read_file(fd, saved);
	if (!saved)
		return (NULL);
	line = ft_new_line(saved);
	if (!line)
		return (ft_free_gnl(&saved));
	saved = ft_clean_saved(saved);
	return (line);
}
