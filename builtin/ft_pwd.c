/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iblanco- <iblanco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 18:00:55 by iblanco-          #+#    #+#             */
/*   Updated: 2023/12/15 16:09:26 by iblanco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int ft_pwd(void)
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