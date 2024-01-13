/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inigo <inigo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 18:24:01 by iblanco-          #+#    #+#             */
/*   Updated: 2024/01/13 19:18:16 by inigo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//CUIDADO CON EL FREE DE NAME Y VALUE PORQUE IGUAL NO TENIA MALLOCADO NADA
void	remove_env(t_cmds *cmds, t_env *current, t_env *prev)
{
	if (prev == NULL)
		cmds->env = current->next;
	else
		prev->next = current->next;
	printf("\nname = %s\n", current->name);
	free(current->name);
	free(current->value);
	free(current);
}

void	find_env(char *opts, t_cmds *cmds)
{
	t_env	*prev;
	t_env	*current;

	prev = NULL;
	current = cmds->env;
	while (current)
	{
		if (ft_strcmp(current->name, opts) == 0)
			return (remove_env(cmds, current, prev));
		prev = current;
		current = prev->next;
	}
}

int	ft_unset(t_cmds *cmds)
{
	int		i;

	i = 0;
	if (cmds->opts == NULL || cmds->opts[0] == NULL
		|| check_alpha_env(cmds, cmds->opts[0], "unset") == 0)
		return (0);
	while (cmds->opts[i])
	{
		find_env(cmds->opts[i], cmds);
		i++;
	}
	return (0);
}
