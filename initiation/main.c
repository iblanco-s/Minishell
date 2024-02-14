/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inigo <inigo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 18:19:28 by iblanco-          #+#    #+#             */
/*   Updated: 2024/02/14 12:29:55 by inigo            ###   ########.fr       */
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

void	free_general(t_cmds *cmds)
{
	if (cmds)
	{
		if (cmds->env)
			ft_free_envs(cmds->env);
		free(cmds);
	}
}

void	ft_error(char *msg, t_cmds *cmds)
{
	ft_putstr_fd(msg, 2);
	free_general(cmds);
	exit(EXIT_FAILURE);
}

void	main_loop(t_cmds *cmds)
{
	char	*line;

	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
			ft_error("minishell: init: readline error", cmds);
		add_history(line);
		handle_input(line, cmds);
		//ejecutar linea
		//free line
		//MAKE HACE RELINK
	}
}

int	main(int argc, char **argv, char **env)
{
	if (argc > 1 && argv)
		ft_error(ERROR_MANY_ARGS, NULL);
	main_loop(setup_program(env));
}
