/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iblanco- <iblanco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 18:51:36 by inigo             #+#    #+#             */
/*   Updated: 2024/04/24 16:32:59 by iblanco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	check_n_case(char **opts)
{
	int	i;

	i = 2;
	if (!(opts[0][0] && opts[0][1]))
		return (0);
	if (!(opts[0][0] == '-' && opts[0][1] == 'n'))
		return (0);
	while (opts[0][i])
	{
		if (opts[0][i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	ft_echo(char **opts)
{
	int		i;
	int		j;

	j = 0;
	if (opts == NULL || opts[0] == NULL)
	{
		printf("\n");
		return (0);
	}
	j = check_n_case(opts);
	i = j;
	while (opts[i])
	{
		printf("%s", opts[i]);
		if (opts[i + 1])
			printf(" ");
		i++;
	}
	if (j == 0)
		printf("\n");
	return (0);
}
