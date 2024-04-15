/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isbuiltin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsalaber <jsalaber@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 09:21:18 by jsalaber          #+#    #+#             */
/*   Updated: 2024/04/15 09:21:20 by jsalaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_is_builtin(t_cmds *cmds)
{
	int	len;

	if (!cmds->opts[0])
		return (0);
	len = ft_strlen(cmds->opts[0]);
	if (!ft_strncmp(cmds->opts[0], "cd", len) && len == 2)
		return (1);
	if (!ft_strncmp(cmds->opts[0], "echo", len) && len == 4)
		return (1);
	if (!ft_strncmp(cmds->opts[0], "env", len) && len == 3)
		return (1);
	if (!ft_strncmp(cmds->opts[0], "exit", len) && len == 4)
		return (1);
	if (!ft_strncmp(cmds->opts[0], "export", len) && len == 6)
		return (1);
	if (!ft_strncmp(cmds->opts[0], "pwd", len) && len == 3)
		return (1);
	if (!ft_strncmp(cmds->opts[0], "unset", len) && len == 5)
		return (1);
	return (0);
}
