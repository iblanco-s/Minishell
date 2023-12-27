/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iblanco- <iblanco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 18:42:26 by iblanco-          #+#    #+#             */
/*   Updated: 2023/12/27 17:19:36 by iblanco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_isdigit(int a)
{
	if ('0' <= a && a <= '9')
		return (1);
	return (0);
}

int	ft_isalpha(int a)
{
	if (('A' <= a && a <= 'Z') || ('a' <= a && a <= 'z'))
		return (1);
	else
		return (-1);
}

int	check_alpha_env(t_cmds *cmds, char *str, char *name_command)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (ft_isalpha(str[i]))
			return (1);
		i++;
	}
	printf("minishell: %s: `%s': not a valid identifier\n",
		name_command, cmds->opts[0]);
	return (0);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	n;
	int	a;

	i = 0;
	n = 1;
	a = 0;
	while (str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r'))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			n *= -1;
		i++;
	}
	while ('0' <= str[i] && str[i] <= '9' && str[i] != '\0')
	{
		a = (a * 10) + (str[i] - '0');
		i++;
	}
	return (a * n);
}

int	change_env_value(t_cmds *cmds, char *name_env, char *value_env)
{
	t_env	*node;

	node = cmds->env;
	while (node)
	{
		if (ft_strcmp(node->name, name_env) == 0)
		{
			if (node->value) 
				free(node->value);
			node->value = value_env;
			return (1);
		}
		node = node->next;
	}
	return (0);
}
