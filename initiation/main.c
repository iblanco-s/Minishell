/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iblanco- <iblanco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 18:19:28 by iblanco-          #+#    #+#             */
/*   Updated: 2024/01/02 18:50:19 by iblanco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_error(char *msg)
{
	ft_putendl_fd(msg, 2);
}
int	main(int argc, char **argv, char **env)
{
	if (argc > 1 && argv)
		ft_error("minishell: init: too many arguments");
	env_to_list(env);	
}