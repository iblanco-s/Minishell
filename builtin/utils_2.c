/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iblanco- <iblanco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 18:42:26 by iblanco-          #+#    #+#             */
/*   Updated: 2024/04/24 16:55:25 by iblanco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	check_alpha_env(char *opts, char *str, char *name)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (!ft_isalpha(str[i]))
		{
			printf("minishell: %s: `%s': not a valid identifier\n",
				name, opts);
			return (0);
		}
		i++;
	}
	return (1);
}

int	change_env_value(t_shell *shell, char *name_env, char *value_env)
{
	t_env	*node;

	node = shell->env;
	while (node)
	{
		if (!node->name || node->local == 0)
		{
			node = node->next;
			continue ;
		}
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
