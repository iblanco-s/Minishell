/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iblanco- <iblanco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 16:50:44 by iblanco-          #+#    #+#             */
/*   Updated: 2024/04/24 16:55:18 by iblanco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	create_enviroment(
	char **opts, t_shell *shell, char *name_env, int equal_sign)
{
	t_env	*node;
	char	*value_env;

	value_env = ft_strdup(&opts[0][equal_sign] + 1);
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

int	ft_export(char **opts, t_shell *shell)
{
	char	*name_env;
	int		equal_sign;

	equal_sign = 0;
	if (opts == NULL || opts[0] == NULL)
		return (no_args_case(shell));
	while (opts[0][equal_sign] != '=' && opts[0][equal_sign])
		equal_sign++;
	if (opts[0][equal_sign] && equal_sign > 0)
	{
		name_env = ft_strndup(opts[0], equal_sign - 1);
		if (!check_alpha_env(opts, name_env, "export"))
			return (0);
		return (create_enviroment(opts, shell, name_env, equal_sign));
	}
	else
		printf("minishell: export: `%s': not a valid identifier\n",
			opts[0]);
	return (0);
}
