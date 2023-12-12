/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iblanco- <iblanco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 18:00:55 by iblanco-          #+#    #+#             */
/*   Updated: 2023/12/12 18:17:54 by iblanco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int ft_pwd(t_cmds *cmds)
{
	char	*pwd;
	int		ret;

	cmds = NULL;
	pwd = NULL;
	ret = 1;
	pwd = getcwd(pwd, sizeof(pwd));
	if (pwd != NULL)
		printf("%s", pwd);
	else
		ret = 0;
	return ret;
}