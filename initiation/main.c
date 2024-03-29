/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inigo <inigo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 18:19:28 by iblanco-          #+#    #+#             */
/*   Updated: 2024/03/29 11:10:14 by inigo            ###   ########.fr       */
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

/**
 * @brief Si hay un error, salir por aqui, 
 * donde se liberara la memoria y sacar mensaje de error
 * 
 * @param msg Mensaje de error
 * @param cmds Estructura con los env ya obtenidos para free
*/
void	ft_error(char *msg, t_cmds *cmds)
{
	ft_putstr_fd(msg, 2);
	free_general(cmds);
	exit(EXIT_FAILURE);
}

/**
 * @brief Loop principal del minishell
 * donde se leera la entrada del usuario
 * y se procesara una y otra vez 
 * 
 * @param cmds Estructura con los env ya obtenidos
*/
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
		// TODO: ejecutar linea y liberar memoria de la linea
	}
}

// ENTRY POINT
int	main(int argc, char **argv, char **env)
{
	// NO PERMITIR ARGUMENTOS SOLO ./MINISHELL
	if (argc > 1 && argv)
		ft_error(ERROR_MANY_ARGS, NULL);
	main_loop(setup_program(env));
}
