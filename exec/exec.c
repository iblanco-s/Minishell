/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junesalaberria <junesalaberria@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 13:25:14 by junesalaber       #+#    #+#             */
/*   Updated: 2024/04/19 16:47:32 by junesalaber      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	manage_redir(t_shell *shell, int *in_copy, int *out_copy)
{
	int		infile;
	int		outfile;

	*in_copy = dup(STDIN_FILENO);
	*out_copy = dup(STDOUT_FILENO);
	if (shell->cmds.infile)
	{
		infile = open_infile(shell->cmds.infile, &shell->cmds.infile_fd);
		dup2(infile, STDIN_FILENO);
		close(infile);
	}
	if (shell->cmds.outfile)
	{
		create_outfile(shell->cmds.outfile);
		outfile = outfile_type(shell->cmds.outfile, &shell->cmds.outfile_fd);
		dup2(outfile, STDOUT_FILENO);
	}
}

char	*ft_get_path(char *path, char *cmd)
{
	char	**split_path;
	char	*exec_path;
	char	*part_path;
	int		i;

	split_path = ft_split(path, ':');
	if (!split_path)
		return (NULL);
	i = -1;
	while (split_path[++i])
	{
		part_path = ft_strjoin(split_path[i], "/");
		exec_path = ft_strjoin(part_path, cmd);
		free(part_path);
		if (access(exec_path, X_OK) )
			return (exec_path);
		free(exec_path);
	}
	free(split_path);
	return (NULL);		
}

void	exec_cmd(t_shell *shell, char **cmd)
{
	char	*path;

	if (!*cmd)
		exit (0);
	if (ft_is_builtin(shell))
		exec_builtin(shell);
	if (!ft_strchr(cmd[0], '/'))
		path = ft_get_path(shell->env->value, cmd[0]);
	else if (access(shell->cmds.opts[0], X_OK) == 0)
		path = ft_strdup(cmd[0]);
	else
		path = NULL;
	if (!path)
	{
		ft_putendl_fd("Command not found", 2);
		exit (127);
	}
	if (execve(path, cmd, &shell->env->value) == -1)
	{
		free(path);
		ft_putendl_fd("Error executing command", 2);
		exit (127);
	}
}

void manage_exec(t_shell *shell)
{
	if (!shell->cmds.next->opts && ft_is_builtin(shell))
		exec_single_builtin(shell);
	else
		exec_pipe(shell, &shell->cmds);
}
