/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isbuiltin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junesalaberria <junesalaberria@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 09:21:18 by jsalaber          #+#    #+#             */
/*   Updated: 2024/04/19 16:16:06 by junesalaber      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_is_builtin(t_shell *shell)
{
	int	len;

	if (!shell->cmds.opts[0])
		return (0);
	len = ft_strlen(shell->cmds.opts[0]);
	if (!ft_strncmp(shell->cmds.opts[0], "cd", len) && len == 2)
		return (1);
	if (!ft_strncmp(shell->cmds.opts[0], "echo", len) && len == 4)
		return (1);
	if (!ft_strncmp(shell->cmds.opts[0], "env", len) && len == 3)
		return (1);
	if (!ft_strncmp(shell->cmds.opts[0], "exit", len) && len == 4)
		return (1);
	if (!ft_strncmp(shell->cmds.opts[0], "export", len) && len == 6)
		return (1);
	if (!ft_strncmp(shell->cmds.opts[0], "pwd", len) && len == 3)
		return (1);
	if (!ft_strncmp(shell->cmds.opts[0], "unset", len) && len == 5)
		return (1);
	return (0);
}

void	exec_builtin(t_shell *shell)
{
	if (!shell->cmds.opts[0])
		return ;
	if (!ft_strncmp(shell->cmds.opts[0], "cd", 2))
		ft_cd(shell);
	else if (!ft_strncmp(shell->cmds.opts[0], "echo", 4))
		ft_echo(shell);
	else if (!ft_strncmp(shell->cmds.opts[0], "env", 3))
		ft_env(shell);
	else if (!ft_strncmp(shell->cmds.opts[0], "exit", 4))
		ft_exit(shell);
	else if (!ft_strncmp(shell->cmds.opts[0], "export", 6))
		ft_export(shell);
	else if (!ft_strncmp(shell->cmds.opts[0], "pwd", 3))
		ft_pwd();
	else if (!ft_strncmp(shell->cmds.opts[0], "unset", 5))
		ft_unset(shell);
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
