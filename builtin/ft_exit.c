/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iblanco- <iblanco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 19:48:58 by inigo             #+#    #+#             */
/*   Updated: 2023/12/14 18:51:45 by iblanco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_exit(t_cmds *cmds)
{
	int i;

	i = 0;
	if (cmds->opts == NULL || cmds->opts[0] == NULL)
		exit(0);
	if (cmds->opts[1] != NULL)
	{
		printf("exit\n");
		printf("minishell: exit: too many arguments\n");
		return (1);
	}
	while (cmds->opts[0][i])
	{
		if (ft_isdigit(cmds->opts[0][i]) == 0)
		{
			printf("exit\n");
			printf("minishell: exit: %s: numeric argument required\n", cmds->opts[0]);
			exit(255);
		}
		i++;
	}
	exit(ft_atoi(cmds->opts[0]));
}