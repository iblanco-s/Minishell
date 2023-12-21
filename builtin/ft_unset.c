/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iblanco- <iblanco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 18:24:01 by iblanco-          #+#    #+#             */
/*   Updated: 2023/12/21 19:28:40 by iblanco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//CUIDADO CON EL FREE DE NAME Y VALUE PORQUE IGUAL NO TENIA MALLOCADO NADA
int	remove_env(t_cmds *cmds, t_env *current, t_env *prev)
{
	if (prev == NULL)
		cmds->env = current->next;
	else
		prev->next = current->next;
	free(current->name);
	free(current->value);
	free(current);
	return (1);
}

int	ft_unset(t_cmds *cmds)
{
	t_env	*prev;
	t_env	*current;

	prev = NULL;
	current = cmds->env;
	if (cmds->opts == NULL || cmds->opts[0] == NULL
		|| check_alpha_env(cmds, cmds->opts[0], "unset") == 0)
		return (0);
	while (current != NULL)
	{
		if (ft_strcmp(current->name, cmds->opts[0]) == 0)
			remove_env(cmds, current, prev);
		prev = current;
		current = current->next;
	}
	return (0);
}
