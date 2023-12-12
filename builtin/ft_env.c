/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iblanco- <iblanco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 17:55:57 by iblanco-          #+#    #+#             */
/*   Updated: 2023/12/12 18:46:16 by iblanco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int ft_env(t_cmds *cmds)
{
	t_env 	*env;
	t_env 	*aux;
	int		ret;

	ret = 0;
	env = cmds->env;
	while (env != NULL)
	{
		printf("%s=%s\n", env->name, env->value);
		aux = env->next;
		env = aux;
		ret = 1;
	}
	return (ret);
}