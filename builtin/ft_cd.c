/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iblanco- <iblanco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 17:49:01 by iblanco-          #+#    #+#             */
/*   Updated: 2023/12/21 17:50:43 by iblanco-         ###   ########.fr       */
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

int	go_to_home(t_cmds *cmds)
{
	char	*home;
	int		ret;

	home = get_env_value(cmds, "HOME");
	if (home == NULL)
	{
		printf("minishell: cd: HOME not set\n");
		return (1);
	}
	ret = chdir(home);
	change_pwd_and_oldpwd(cmds);
	return (ret);
}

int	go_to_previous_directory(t_cmds *cmds)
{
	char	*oldpwd;
	int		ret;

	ret = 0;
	oldpwd = get_env_value(cmds, "OLDPWD");
	if (oldpwd == NULL)
	{
		printf("minishell: cd: OLDPWD not set\n");
		return (1);
	}
	else
	{
		ret = chdir(oldpwd);
		if (ret == 0)
			printf("%s\n", oldpwd);
		change_pwd_and_oldpwd(cmds);
	}
	return (ret);
}

int	go_to_current_directory(t_cmds *cmds)
{
	char	*pwd;
	int		ret;

	pwd = get_env_value(cmds, "PWD");
	if (pwd == NULL)
		return (0);
	ret = chdir(pwd);
	change_pwd_and_oldpwd(cmds);
	return (ret);
}

int	go_to_parent_directory(t_cmds *cmds)
{
	int	ret;

	ret = chdir("..");
	change_pwd_and_oldpwd(cmds);
	return (ret);
}

	// else if (ft_strcmp(cmds->opts[0], "/") == 0)
	// 	return go_to_path(cmds, cmds->opts[0]);

int	ft_cd(t_cmds *cmds)
{
	if (cmds->opts == NULL || cmds->opts[0] == NULL
		|| ft_strcmp(cmds->opts[0], "~") == 0)
		return (go_to_home(cmds));
	else if (ft_strcmp(cmds->opts[0], "..") == 0)
		return (go_to_parent_directory(cmds));
	else if (ft_strcmp(cmds->opts[0], "-") == 0)
		return (go_to_previous_directory(cmds));
	else if (ft_strcmp(cmds->opts[0], ".") == 0)
		return (go_to_current_directory(cmds));
	else
		return (go_to_path(cmds, cmds->opts[0]));
}
