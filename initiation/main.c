/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsalaber <jsalaber@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 18:19:28 by iblanco-          #+#    #+#             */
/*   Updated: 2024/04/24 11:22:14 by jsalaber         ###   ########.fr       */
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
		free(shell);
	}
}

/**
 * @brief Si hay un error, salir por aqui, 
 * donde se liberara la memoria y sacar mensaje de error
 * 
 * @param msg Mensaje de error
 * @param shell Estructura con los env ya obtenidos para free
*/
// void	ft_error(char *msg, t_shell *shell)
// {
// 	ft_putstr_fd(msg, 2);
// 	free_general(shell);
// 	exit(EXIT_FAILURE);
// }

/**
 * @brief Loop principal del minishell
 * donde se leera la entrada del usuario
 * y se procesara una y otra vez 
 * 
 * @param shell Estructura con los env ya obtenidos
*/
void	main_loop(t_shell *shell)
{
	char	*line;

	while (1)
	{
		line = readline("minishell$ ");
		// if (!line)
		// 	ft_error(shell, "minishell: init: readline error", 1);
		add_history(line);
		handle_input(line, shell);
		manage_exec(shell);
		// TODO: ejecutar linea y liberar memoria de la linea
	}
}

// ENTRY POINT
int	main(int argc, char **argv, char **env)
{
	// NO PERMITIR ARGUMENTOS SOLO ./MINISHELL
	if (argc > 1 && argv)
		ft_error(NULL, ERROR_MANY_ARGS, 1);
	main_loop(setup_program(env));
}
