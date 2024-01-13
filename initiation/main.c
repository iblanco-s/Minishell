/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inigo <inigo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 18:19:28 by iblanco-          #+#    #+#             */
/*   Updated: 2024/01/13 19:14:14 by inigo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	free_general(t_cmds *cmds)
{
	//free cmds
	//free env
	printf("%s", cmds->env->name);
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
		//parsear linea
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
