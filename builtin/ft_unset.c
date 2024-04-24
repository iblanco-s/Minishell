/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iblanco- <iblanco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 18:24:01 by iblanco-          #+#    #+#             */
/*   Updated: 2024/04/24 16:43:36 by iblanco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//CUIDADO CON EL FREE DE NAME Y VALUE PORQUE IGUAL NO TENIA MALLOCADO NADA
void	remove_env(t_shell *shell, t_env *current, t_env *prev)
{
	if (prev == NULL)
		shell->env = current->next;
	else
		prev->next = current->next;
	free(current->name);
	free(current->value);
	free(current);
}

void	find_env(char *opts, t_shell *shell)
{
	t_env	*prev;
	t_env	*current;

	prev = NULL;
	current = shell->env;
	while (current)
	{
		if (ft_strcmp(current->name, opts) == 0)
			return (remove_env(shell, current, prev));
		prev = current;
		current = prev->next;
	}
}

int	ft_unset(char **opts, t_shell *shell)
{
	int		i;

	i = 0;
	if (opts == NULL || opts[0] == NULL
		|| check_alpha_env(opts, opts[0], "unset") == 0)
		return (0);
	while (opts[i])
	{
		find_env(opts[i], shell);
		i++;
	}
	return (0);
}
