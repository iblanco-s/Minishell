/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isbuiltin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsalaber <jsalaber@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 09:21:18 by jsalaber          #+#    #+#             */
/*   Updated: 2024/04/22 18:01:31 by jsalaber         ###   ########.fr       */
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

int	ft_is_builtin(t_shell *shell)
{
	int	len;

	if (!shell->cmds->opts || !shell->cmds->opts[0])
		return (0);
	len = ft_strlen(shell->cmds->opts[0]);
	if (!ft_strncmp(shell->cmds->opts[0], "cd", len) && len == 2)
		return (1);
	if (!ft_strncmp(shell->cmds->opts[0], "echo", len) && len == 4)
		return (2);
	if (!ft_strncmp(shell->cmds->opts[0], "env", len) && len == 3)
		return (3);
	if (!ft_strncmp(shell->cmds->opts[0], "exit", len) && len == 4)
		return (4);
	if (!ft_strncmp(shell->cmds->opts[0], "export", len) && len == 6)
		return (5);
	if (!ft_strncmp(shell->cmds->opts[0], "pwd", len) && len == 3)
		return (6);
	if (!ft_strncmp(shell->cmds->opts[0], "unset", len) && len == 5)
		return (7);
	return (0);
}

void	cut_first_opt(char **opts)
{
	int	i;

	if (opts == NULL || opts[0] == NULL)
		return ;
	free(opts[0]);
	i = 0;
	while (opts[i + 1] != NULL)
	{
		opts[i] = opts[i + 1];
		i++;
	}
	opts[i] = NULL;
}

int	exec_builtin(t_shell *shell)
{
	int	builtin;

	builtin = ft_is_builtin(shell);
	if (builtin == 0)
		return (0);
	cut_first_opt(shell->cmds->opts);
	if (builtin == 1)
		return (ft_cd(shell), 1);
	else if (builtin == 2)
		return (ft_echo(shell), 1);
	else if (builtin == 3)
		return (ft_env(shell), 1);
	else if (builtin == 4)
		return (ft_exit(shell), 1);
	else if (builtin == 5)
		return (ft_export(shell), 1);
	else if (builtin == 6)
		return (ft_pwd(), 1);
	else if (builtin == 7)
		return (ft_unset(shell), 1);
	return (0);
}

void	exec_single_builtin(t_shell *shell)
{
	int		in_copy;
	int		out_copy;

	manage_redir(shell, &in_copy, &out_copy);
	exec_builtin(shell);
	dup2(in_copy, STDIN_FILENO);
	dup2(out_copy, STDOUT_FILENO);
	close(in_copy);
	close(out_copy);
}
