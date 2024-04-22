/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsalaber <jsalaber@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 13:25:14 by junesalaber       #+#    #+#             */
/*   Updated: 2024/04/22 14:09:26 by jsalaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	manage_redir(t_shell *shell, int *in_copy, int *out_copy)
{
	int		infile;
	int		outfile;

	*in_copy = dup(STDIN_FILENO);
	*out_copy = dup(STDOUT_FILENO);
	if (shell->cmds->infile)
	{
		infile = open_infile(shell->cmds->infile, shell->cmds->infile_fd);
		dup2(infile, STDIN_FILENO);
		close(infile);
	}
	if (shell->cmds->outfile)
	{
		create_outfile(shell->cmds->outfile);
		outfile = outfile_type(shell->cmds->outfile, shell->cmds->outfile_fd);
		dup2(outfile, STDOUT_FILENO);
	}
}

void	ft_free_split(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
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
		if (access(exec_path, F_OK | X_OK) == 0)
		{
			ft_free_split(split_path);
			return (exec_path);
		}
		free(exec_path);
	}
	ft_free_split(split_path);
	return (NULL);
}

void	exec_cmd(t_shell *shell, char **cmd)
{
	char	*path;
	char	*path_value;

	if (!*cmd)
		exit (0);
	if (exec_builtin(shell))
		return ;
	path_value = get_env_value(shell, "PATH");
	if (!ft_strchr(cmd[0], '/'))
		path = ft_get_path(path_value, cmd[0]);
	else if (access(cmd[0], X_OK) == 0)
		path = ft_strdup(cmd[0]);
	else
		path = NULL;
	if (!path)
	{
		ft_putendl_fd("Command not found", 2);
		exit (127);
	}
	char *envp[] = {path_value, NULL};
	if (execve(path, cmd, envp) == -1)
	{
		free(path);
		ft_putendl_fd("Error executing command", 2);
		exit (127);
	}
}

void	manage_exec(t_shell *shell)
{
	if (!shell)
		{
			ft_putendl_fd("no hay lista", 2);
        	return ;
		}
	if (shell->cmds->next && !shell->cmds->next->opts && ft_is_builtin(shell))
		exec_single_builtin(shell);
	else
		exec_pipe(shell, shell->cmds);
}
