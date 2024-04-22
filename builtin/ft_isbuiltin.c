/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isbuiltin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsalaber <jsalaber@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 09:21:18 by jsalaber          #+#    #+#             */
/*   Updated: 2024/04/22 13:50:22 by jsalaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_is_builtin(t_shell *shell)
{
	int	len;

	if (!shell->cmds->opts[0])
		return (0);
	len = ft_strlen(shell->cmds->opts[0]);
	if (!ft_strncmp(shell->cmds->opts[0], "cd", len) && len == 2)
		return (1);
	if (!ft_strncmp(shell->cmds->opts[0], "echo", len) && len == 4)
		return (1);
	if (!ft_strncmp(shell->cmds->opts[0], "env", len) && len == 3)
		return (1);
	if (!ft_strncmp(shell->cmds->opts[0], "exit", len) && len == 4)
		return (1);
	if (!ft_strncmp(shell->cmds->opts[0], "export", len) && len == 6)
		return (1);
	if (!ft_strncmp(shell->cmds->opts[0], "pwd", len) && len == 3)
		return (1);
	if (!ft_strncmp(shell->cmds->opts[0], "unset", len) && len == 5)
		return (1);
	return (0);
}

int	exec_builtin(t_shell *shell)
{
	if (ft_is_builtin(shell))
	{
		if (!ft_strncmp(shell->cmds->opts[0], "cd", 2))
			return (ft_cd(shell), 1);
		else if (!ft_strncmp(shell->cmds->opts[0], "echo", 4))
			return (ft_echo(shell), 1);
		else if (!ft_strncmp(shell->cmds->opts[0], "env", 3))
			return (ft_env(shell), 1);
		else if (!ft_strncmp(shell->cmds->opts[0], "exit", 4))
			return (ft_exit(shell), 1);
		else if (!ft_strncmp(shell->cmds->opts[0], "export", 6))
			return (ft_export(shell), 1);
		else if (!ft_strncmp(shell->cmds->opts[0], "pwd", 3))
			return (ft_pwd(), 1);
		else if (!ft_strncmp(shell->cmds->opts[0], "unset", 5))
			return (ft_unset(shell), 1);
	}
	return (0);
}

void	exec_single_builtin(t_shell *shell)
{
	int		in_copy;
	int		out_copy;

	if (ft_is_builtin(shell))
	{
		manage_redir(shell, &in_copy, &out_copy);
		exec_builtin(shell);
		dup2(in_copy, STDIN_FILENO);
		dup2(out_copy, STDOUT_FILENO);
		close(in_copy);
		close(out_copy);
	}
}
