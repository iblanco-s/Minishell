/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inigo <inigo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 18:00:55 by iblanco-          #+#    #+#             */
/*   Updated: 2023/12/13 17:39:02 by inigo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int ft_pwd()
{
	char	*pwd;
	int		ret;

	pwd = NULL;
	ret = 1;
	pwd = getcwd(pwd, sizeof(pwd));
	if (pwd != NULL)
		printf("%s", pwd);
	else
		ret = 0;
	return ret;
}