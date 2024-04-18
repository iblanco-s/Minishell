/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inigo <inigo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 18:51:36 by inigo             #+#    #+#             */
/*   Updated: 2024/04/14 20:20:37 by inigo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	check_n_case(t_cmds *cmds)
{
	int	i;

	i = 2;
	if (!(cmds->opts[0][0] && cmds->opts[0][1]))
		return (0);
	if (!(cmds->opts[0][0] == '-' && cmds->opts[0][1] == 'n'))
		return (0);
	while (cmds->opts[0][i])
	{
		if (cmds->opts[0][i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	ft_echo(t_shell *shell)
{
	int		i;
	int		j;
	t_cmds	*cmds;

	cmds = &shell->cmds;
	j = 0;
	if (cmds->opts == NULL || cmds->opts[0] == NULL)
	{
		printf("\n");
		return (0);
	}
	j = check_n_case(cmds);
	i = j;
	while (cmds->opts[i])
	{
		printf("%s", cmds->opts[i]);
		if (cmds->opts[i + 1])
			printf(" ");
		i++;
	}
	if (j == 0)
		printf("\n");
	return (0);
}
