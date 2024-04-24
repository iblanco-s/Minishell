/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inigo <inigo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 17:46:49 by inigo             #+#    #+#             */
/*   Updated: 2024/04/14 20:51:54 by inigo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	update_shlvl(t_shell *shell)
{
	char	*value;
	int		lvl;

	value = get_env_value(shell, "SHLVL");
	if (value)
	{
		lvl = ft_atoi(value);
		lvl++;
		change_env_value(shell, "SHLVL", ft_itoa(lvl));
		free(value);
	}
	else
		change_env_value(shell, "SHLVL", "1");
}

t_shell	*setup_program(char **env)
{
	t_shell	*shell;

	shell = malloc(sizeof(t_shell));
	shell->env = env_to_list(env);
	shell->cmds = NULL;
	update_shlvl(shell);
	return (shell);
}
