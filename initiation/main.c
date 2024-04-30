/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsalaber <jsalaber@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 18:19:28 by iblanco-          #+#    #+#             */
/*   Updated: 2024/04/30 18:34:35 by jsalaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	g_exit_status;

void	main_loop(t_shell *shell)
{
	char	*line;

	disable_print_signals();
	while (1)
	{
		is_interactive(1);
		line = readline("minishell$ ");
		if (line == NULL)
		{
			ft_putstr_fd("Quitting minishell\n", 1);
			free_general(shell);
			break ;
		}
		else
		{
			is_interactive(0);
			add_history(line);
			if (handle_input(line, shell))
				manage_exec(shell);
		}
		free_command(shell, line);
	}
}

// ENTRY POINT
int	main(int argc, char **argv, char **env)
{
	g_exit_status = 0;
	if (argc > 1 && argv)
		ft_error(NULL, ERROR_MANY_ARGS, 1);
	main_loop(setup_program(env));
}
