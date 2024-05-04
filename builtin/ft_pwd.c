/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsalaber <jsalaber@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 18:00:55 by iblanco-          #+#    #+#             */
/*   Updated: 2024/04/24 10:56:31 by jsalaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_pwd(void)
{
	char	*pwd;
	int		ret;

	pwd = NULL;
	ret = 1;
	pwd = getcwd(pwd, sizeof(pwd));
	if (pwd != NULL)
		printf("%s\n", pwd);
	else
		ret = 0;
	free(pwd);
	return (ret);
}
