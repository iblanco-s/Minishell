/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iblanco- <iblanco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 17:49:01 by iblanco-          #+#    #+#             */
/*   Updated: 2023/12/14 18:55:24 by iblanco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
//TODO: hacer el ft_cd,
//poner comentarios, revisar leaks, revisar norminette

/*
cd cases:
cd alone= go to home
cd alone without env HOME= ERROR
cd with path= go to path
cd with path that doesnt exist= ERROR
cd with path that is a file= ERROR
cd with path that is a directory= go to directory
cd with path that is a directory but doesnt exist= ERROR
cd ..= go to parent directory
cd - = go to previous directory
cd - with no previous directory= ERROR
cd - with no previous directory and no env OLDPWD= ERROR
cd ~ = go to home
cd ~ with no env HOME= ERROR
cd . = go to current directory
cd . with no env PWD= ERROR
*/
int ft_cd(t_cmds *cmds)
{

}