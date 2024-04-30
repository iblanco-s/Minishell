/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-m <aecm.davidgomez@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 19:48:58 by inigo             #+#    #+#             */
/*   Updated: 2024/04/30 18:01:27 by dgomez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	util_exit(char **opts)
{
	if (opts == NULL || opts[0] == NULL)
	{
		g_exit_status = 0;
		exit(g_exit_status);
	}
}

int	ft_exit(char **opts, t_shell *shell)
{
	int		i;

	i = 0;
	util_exit(opts);
	if (opts[1] != NULL)
	{
		printf("exit\n");
		printf("minishell: exit: too many arguments\n");
		return (1);
	}
	while (opts[0][i])
	{
		if (ft_isdigit(opts[0][i]) == 0)
		{
			printf("exit\n");
			printf("minishell: exit: %s: numeric argument required\n",
				opts[0]);
			g_exit_status = 255;
		}
		i++;
	}
	g_exit_status = ft_atoi(opts[0]);
	free_general(shell);
	exit(g_exit_status);
}
