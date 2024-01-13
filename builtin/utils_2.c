/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inigo <inigo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 18:42:26 by iblanco-          #+#    #+#             */
/*   Updated: 2024/01/13 19:15:55 by inigo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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
