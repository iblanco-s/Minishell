/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iblanco- <iblanco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 19:48:58 by inigo             #+#    #+#             */
/*   Updated: 2024/04/24 16:34:02 by iblanco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_exit(char **opts)
{
	int		i;

	i = 0;
	if (opts == NULL || opts[0] == NULL)
		exit(0);
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
			exit(255);
		}
		i++;
	}
	exit(ft_atoi(opts[0]));
}
