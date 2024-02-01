/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghoyuelo <ghoyuelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 16:52:58 by ghoyuelo          #+#    #+#             */
/*   Updated: 2024/01/11 15:50:57 by ghoyuelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static void	signal_handler(int signal)
{
	if (signal == SIGINT)
	{
		rl_replace_line("", 0);
		write(1, "\n", 1);
		rl_on_new_line();
		rl_redisplay();
		g_error = 1;
	}
	else if (signal == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay();
	}
	return ;
}

static void	child_handler(int signal)
{
	if (signal == SIGINT)
		g_error = 130;
	else if (signal == SIGQUIT)
	{
		write(1, "Quit: 3\n", 10);
		g_error = 131;
	}
	return ;
}
//a signal waiting le pasamos el pid del proceso hijo
void	signal_waiting(int sig)
{
	struct sigaction	sig_act;
	pid_t				pid;

	pid = fork();
	if (pid == -1)
		g_error = 1;
		exit(1);
	else	
	if (pid == 0)
		sig_act.sa_handler = &child_handler;
	else
		sig_act.sa_handler = &csignal_handler;
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
	sigaction(SIGTERM, &sa, NULL);//limpia la memoria
}