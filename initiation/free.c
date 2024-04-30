/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iblanco- <iblanco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 17:10:26 by dgomez-m          #+#    #+#             */
/*   Updated: 2024/04/30 19:01:19 by iblanco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_free_envs(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env->next;
		free(env->name);
		if (env->value)
			free(env->value);
		free(env);
		env = tmp;
	}
}

void	free_general(t_shell *shell)
{
	if (shell)
	{
		if (shell->env)
			ft_free_envs(shell->env);
		if (shell->cmds)
			free_command(shell, NULL);
		free(shell);
	}
}

void	ft_free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	free_command(t_shell *shell, char *line)
{
	t_cmds	*tmp;
	t_cmds	*tmp2;

	tmp = shell->cmds;
	if (line)
		free(line);
	if (tmp)
	{
		while (tmp)
		{
			if (tmp->opts)
				ft_free_array(tmp->opts);
			if (tmp->infile)
				ft_free_array(tmp->infile);
			if (tmp->outfile)
				ft_free_array(tmp->outfile);
			if (tmp->infile_fd)
				free(tmp->infile_fd);
			if (tmp->outfile_fd)
				free(tmp->outfile_fd);
			tmp2 = tmp->next;
			free(tmp);
			tmp = tmp2;
		}
	}
}
