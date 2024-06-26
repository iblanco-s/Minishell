/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsalaber <jsalaber@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 10:31:05 by jsalaber          #+#    #+#             */
/*   Updated: 2024/04/29 12:40:43 by jsalaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_error(t_shell *shell, char *error_msg, int exit_status)
{
	if (shell)
		free_general(shell);
	ft_putendl_fd(error_msg, 2);
	exit(exit_status);
}

void	ft_continue_error(char *error_msg)
{
	ft_putstr_fd(error_msg, 2);
	return ;
}

void	ft_pipe(int pipe_fd[2])
{
	pipe_fd[0] = 33;
	pipe_fd[1] = 33;
}

void	ft_free_split(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}
