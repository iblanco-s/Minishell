/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iblanco- <iblanco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 16:50:44 by iblanco-          #+#    #+#             */
/*   Updated: 2023/12/27 17:04:54 by iblanco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	create_enviroment(t_cmds *cmds, char *name_env, int equal_sign)
{
	t_env	*node;
	char	*value_env;

	value_env = ft_strdup(&cmds->opts[0][equal_sign] + 1);
	if (change_env_value(cmds, name_env, value_env) == 0)
	{
		node = (t_env *)malloc(sizeof(t_env));
		node->name = name_env;
		node->value = value_env;
		node->next = NULL;
		ft_lstadd_back(&cmds->env, node);
	}
	return (1);
}

int	no_args_case(t_cmds *cmds)
{
	t_env	*node;

	node = cmds->env;
	while (node)
	{
		if (node->value)
			printf("declare -x %s=\"%s\"\n", node->name, node->value);
		else
			printf("declare -x %s\n", node->name);
		node = node->next;
	}
	return (0);
}

int	ft_export(t_cmds *cmds)
{
	char	*name_env;
	int		equal_sign;

	equal_sign = 0;
	if (cmds->opts == NULL || cmds->opts[0] == NULL)
		return (no_args_case(cmds));
	while (cmds->opts[0][equal_sign] != '=' && cmds->opts[0][equal_sign])
		equal_sign++;
	if (cmds->opts[0][equal_sign] && equal_sign > 0)
	{
		name_env = ft_strndup(cmds->opts[0], equal_sign - 1);
		if (check_alpha_env(cmds, name_env, "export") == 0)
			return (0);
		return (create_enviroment(cmds, name_env, equal_sign));
	}
	else
		printf("minishell: export: `%s': not a valid identifier\n",
			cmds->opts[0]);
	return (0);
}
