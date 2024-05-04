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
		node->local = 1;
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

void	create_enviroment_local(char *name, t_env *env)
{
	t_env	*node;

	node = (t_env *)malloc(sizeof(t_env));
	node->name = ft_strdup(name);
	node->value = NULL;
	node->local = 0;
	node->next = NULL;
	ft_lstadd_back(&env, node);
}

void	export_loop(t_shell *shell, char **opts, char *name_env)
{
	int		i;
	int		equal_sign;

	i = 0;
	while (opts[i])
	{
		equal_sign = 0;
		while (opts[i][equal_sign] && opts[i][equal_sign] != '=')
			equal_sign++;
		if (opts[i][equal_sign] && equal_sign > 0)
		{
			name_env = ft_strndup(opts[i], equal_sign - 1);
			if (!check_alpha_env(opts[i], name_env, "export"))
				return ;
			create_enviroment(opts, shell, name_env, equal_sign);
		}
		else
		{
			if (!check_alpha_env(opts[i], opts[i], "export"))
				return ;
			if (get_env_value(shell, opts[i]) == NULL)
				create_enviroment_local(opts[i], shell->env);
		}
		i++;
	}
}

int	ft_export(char **opts, t_shell *shell)
{
	char	*name_env;

	name_env = NULL;
	if (opts == NULL || opts[0] == NULL)
		return (no_args_case(shell));
	export_loop(shell, opts, name_env);
	return (0);
}
