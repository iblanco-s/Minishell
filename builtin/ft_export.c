/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inigo <inigo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 16:50:44 by iblanco-          #+#    #+#             */
/*   Updated: 2024/04/21 13:08:05 by inigo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	create_enviroment(t_shell *shell, char *name_env, int equal_sign)
{
	t_env	*node;
	char	*value_env;
	t_cmds	*cmds;

	cmds = shell->cmds;
	value_env = ft_strdup(&cmds->opts[0][equal_sign] + 1);
	if (change_env_value(shell, name_env, value_env) == 0)
	{
		node = (t_env *)malloc(sizeof(t_env));
		node->name = name_env;
		node->value = value_env;
		node->next = NULL;
		ft_lstadd_back(&shell->env, node);
	}
	return (1);
}

int	no_args_case(t_shell *shell)
{
	t_env	*node;

	node = shell->env;
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

int	ft_export(t_shell *shell)
{
	char	*name_env;
	int		equal_sign;
	t_cmds	*cmds;

	cmds = shell->cmds;
	equal_sign = 0;
	if (cmds->opts == NULL || cmds->opts[0] == NULL)
		return (no_args_case(shell));
	while (cmds->opts[0][equal_sign] != '=' && cmds->opts[0][equal_sign])
		equal_sign++;
	if (cmds->opts[0][equal_sign] && equal_sign > 0)
	{
		name_env = ft_strndup(cmds->opts[0], equal_sign - 1);
		if (check_alpha_env(cmds, name_env, "export") == 0)
			return (0);
		return (create_enviroment(shell, name_env, equal_sign));
	}
	else
		printf("minishell: export: `%s': not a valid identifier\n",
			cmds->opts[0]);
	return (0);
}
