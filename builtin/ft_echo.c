/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iblanco- <iblanco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 18:51:36 by inigo             #+#    #+#             */
/*   Updated: 2023/12/21 18:55:40 by iblanco-         ###   ########.fr       */
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

int	ft_echo(t_cmds *cmds)
{
	int	i;
	int	j;

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