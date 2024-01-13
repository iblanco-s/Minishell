/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inigo <inigo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 17:46:49 by inigo             #+#    #+#             */
/*   Updated: 2024/01/13 19:13:30 by inigo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	update_shlvl(t_cmds *cmds)
{
	char	*value;
	int		lvl;

	value = get_env_value(cmds, "SHLVL");
	if (value)
	{
		lvl = ft_atoi(value);
		lvl++;
		change_env_value(cmds, "SHLVL", ft_itoa(lvl));
	}
	else
		change_env_value(cmds, "SHLVL", "1");
}

t_cmds	*setup_program(char **env)
{
	t_cmds	*cmds;

	cmds = malloc(sizeof(t_cmds));
	cmds->env = env_to_list(env);
	update_shlvl(cmds);
	return (cmds);
}
