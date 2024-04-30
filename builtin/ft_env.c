/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inigo <inigo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 17:55:57 by iblanco-          #+#    #+#             */
/*   Updated: 2024/04/14 20:21:11 by inigo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_env(t_shell *shell)
{
	t_env	*env;
	t_env	*aux;
	int		ret;

	ret = 0;
	env = shell->env;
	while (env != NULL)
	{
		if (env->local == 0)
		{
			aux = env->next;
			env = aux;
			continue ;
		}
		if (env->value)
			printf("%s=%s\n", env->name, env->value);
		else
			printf("%s=\n", env->name);
		aux = env->next;
		env = aux;
		ret = 1;
	}
	return (ret);
}
