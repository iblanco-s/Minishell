/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inigo <inigo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 10:02:54 by inigo             #+#    #+#             */
/*   Updated: 2024/04/28 20:05:09 by inigo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	disable_print_signals(void)
{
	struct termios	termios;

	tcgetattr(STDIN_FILENO, &termios);
	termios.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &termios);
}

void	handle_signal_int_inter(int	sig)
{
	if (sig == SIGINT)
	{
		ft_putstr_fd("\n", STDOUT_FILENO);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	handle_signal_int_no_inter(int	sig)
{
	if (sig == SIGINT)
	{
		g_exit_status = 130;
		ft_putstr_fd("\n", STDOUT_FILENO);
		(void)sig;
	}
}

void	handle_signal_quit_no_inter(int	sig)
{
	if (sig == SIGQUIT)
	{
		g_exit_status = 131;
		ft_putstr_fd("Quit\n", STDOUT_FILENO);
		(void)sig;
	}
}

int	is_interactive(int change)
{
	static int	interactive;

	if (change == -1)
		return (interactive);
	interactive = change;
	if (interactive == 1)
	{
		signal(SIGINT, handle_signal_int_inter);
		signal(SIGQUIT, SIG_IGN);
	}
	else
	{
		signal(SIGINT, handle_signal_int_no_inter);
		signal(SIGQUIT, handle_signal_quit_no_inter);
	}
	return (0);
}
