/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_reddirections.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inigo <inigo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 12:50:39 by inigo             #+#    #+#             */
/*   Updated: 2024/04/21 12:51:37 by inigo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	*append_to_reddir_type_array(int *reddir_types, int new_reddir_type)
{
	int	*new_reddir_types;
	int	size;
	int	i;

	size = 0;
	if (reddir_types != NULL)
	{
		while (reddir_types[size] != -1)
			size++;
	}
	new_reddir_types = (int *)malloc((size + 2) * sizeof(int));
	i = 0;
	while (i < size)
	{
		new_reddir_types[i] = reddir_types[i];
		i++;
	}
	new_reddir_types[i] = new_reddir_type;
	new_reddir_types[i + 1] = -1;
	if (reddir_types != NULL)
		free(reddir_types);
	return (new_reddir_types);
}

char	**append_to_files_array(char **files, char *new_file)
{
	char	**new_files;
	int		size;
	int		i;

	size = 0;
	if (files != NULL)
	{
		while (files[size] != NULL)
			size++;
	}
	new_files = (char **)malloc((size + 2) * sizeof(char *));
	i = 0;
	while (i < size)
	{
		new_files[i] = ft_strdup(files[i]);
		free(files[i]);
		i++;
	}
	new_files[i] = new_file;
	new_files[i + 1] = NULL;
	if (files != NULL)
		free(files);
	return (new_files);
}

void	set_input_redirection(t_cmds *cmd, t_parse **current, int fd_type)
{
	if ((*current)->next)
	{
		cmd->infile = append_to_files_array(
				cmd->infile, ft_strdup((*current)->next->token));
		cmd->infile_fd = append_to_reddir_type_array(cmd->infile_fd, fd_type);
		*current = (*current)->next;
	}
}

void	set_output_redirection(t_cmds *cmd, t_parse **current, int fd_type)
{
	if ((*current)->next)
	{
		cmd->outfile = append_to_files_array(
				cmd->outfile, ft_strdup((*current)->next->token));
		cmd->outfile_fd = append_to_reddir_type_array(cmd->outfile_fd, fd_type);
		*current = (*current)->next;
	}
}
