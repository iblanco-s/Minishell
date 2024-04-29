/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsalaber <jsalaber@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 18:19:28 by iblanco-          #+#    #+#             */
/*   Updated: 2024/04/29 17:07:57 by jsalaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
int g_exit_status;

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
			tmp = tmp->next;
		}
		free(shell->cmds);
		shell->cmds = NULL;
	}
}

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

	// organize_signals();
	disable_print_signals();
	while (1)
	{
		// int in_fd = dup(STDIN_FILENO);
		// int out_fd = dup(STDOUT_FILENO);
		// printf("Input file descriptor: %d\n", in_fd);
		// printf("Output file descriptor: %d\n", out_fd);
		is_interactive(1);
		line = readline("minishell$ ");//aqui se queda parado al llamar minishell en minishell, posiblemente por tema de file descriptors
		if (line == NULL)
		{
			ft_putstr_fd("Quitting minishell\n", 1);
			free_general(shell);
			break;
		} 
		else {
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
