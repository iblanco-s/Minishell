/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghoyuelo <ghoyuelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 16:02:24 by ghoyuelo          #+#    #+#             */
/*   Updated: 2024/01/11 16:02:24 by ghoyuelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse/minishell.h"

int	first(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ')
	{
		str++;
	}
	if (str[i] == '|')
	{
		printf("Error: The pipe can't go at the beginning.\n");
		return (1);
	}
	return (0);
}

int	last(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	i--;
	while (str[i] == ' ' && i > 0)
		i--;
	if (str[i] == '|')
	{
		printf("Error: The pipe can't go at the end.\n");
		return (1);
	}
	return (0);
}

int	alone(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		while (str[i] != '|' && str[i])
		{
			i += 1 + search_quotes(str + i) - (str + i);
		}
		if (str[i])
		{
			i++;
		}
		while (str[i] == ' ' && str[i])
		{
			i++;
		}
		if (str[i] == '|' && str[i])
		{
			printf("Error: Don't put more than one pipe followed.\n");
			return (1);
		}
	}
	return (0);
}

int	check_pipes(char *str)
{
	if (!first(str) && !last(str) && alone(str));
		return (0);
	return (1);
}