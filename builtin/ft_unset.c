/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inigo <inigo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 18:24:01 by iblanco-          #+#    #+#             */
/*   Updated: 2023/12/13 18:35:22 by inigo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int ft_unset(t_cmds *cmds)
{
    t_env *prev = NULL;
    t_env *current = cmds->env;

	if (cmds->opts[0] == NULL || 
			check_alpha_env(cmds, cmds->opts[0], "unset") == 0)
		return (0);
    while (current != NULL)
    {
        if (ft_strcmp(current->name, cmds->opts[0]) == 0)
        {
            if (prev == NULL)
                cmds->env = current->next;
            else
                prev->next = current->next;
            free(current->name);
            free(current->value);
            free(current);
            return 1;
        }
        prev = current;
        current = current->next;
    }
    return 0;	
}
