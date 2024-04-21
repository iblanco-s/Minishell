/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inigo <inigo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 17:49:01 by iblanco-          #+#    #+#             */
/*   Updated: 2024/04/21 13:07:49 by inigo            ###   ########.fr       */
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

int	go_to_home(t_shell *shell)
{
	char	*home;
	int		ret;

	home = get_env_value(shell, "HOME");
	if (home == NULL)
	{
		printf("minishell: cd: HOME not set\n");
		return (1);
	}
	ret = chdir(home);
	change_pwd_and_oldpwd(shell);
	return (ret);
}

int	go_to_previous_directory(t_shell *shell)
{
	char	*oldpwd;
	int		ret;

	ret = 0;
	oldpwd = get_env_value(shell, "OLDPWD");
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
		change_pwd_and_oldpwd(shell);
	}
	return (ret);
}

int	go_to_current_directory(t_shell *shell)
{
	char	*pwd;
	int		ret;

	pwd = get_env_value(shell, "PWD");
	if (pwd == NULL)
		return (0);
	ret = chdir(pwd);
	change_pwd_and_oldpwd(shell);
	return (ret);
}

int	go_to_parent_directory(t_shell *shell)
{
	int	ret;

	ret = chdir("..");
	change_pwd_and_oldpwd(shell);
	return (ret);
}

	// else if (ft_strcmp(cmds->opts[0], "/") == 0)
	// 	return go_to_path(cmds, cmds->opts[0]);

int	ft_cd(t_shell *shell)
{
	if (shell->cmds->opts == NULL || shell->cmds->opts[0] == NULL
		|| ft_strcmp(shell->cmds->opts[0], "~") == 0)
		return (go_to_home(shell));
	else if (ft_strcmp(shell->cmds->opts[0], "..") == 0)
		return (go_to_parent_directory(shell));
	else if (ft_strcmp(shell->cmds->opts[0], "-") == 0)
		return (go_to_previous_directory(shell));
	else if (ft_strcmp(shell->cmds->opts[0], ".") == 0)
		return (go_to_current_directory(shell));
	else
		return (go_to_path(shell, shell->cmds->opts[0]));
}
