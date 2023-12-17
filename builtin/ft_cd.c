/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iblanco- <iblanco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 17:49:01 by iblanco-          #+#    #+#             */
/*   Updated: 2023/12/17 13:46:55 by iblanco-         ###   ########.fr       */
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
char *get_env_value(t_cmds *cmds, char *name)
{
    t_env *current;
	
	current = cmds->env;
    while (current != NULL)
	{
        if (strcmp(current->name, name) == 0)
            return current->value;
        current = current->next;
    }
    return NULL;
}

int create_oldpwd(t_cmds *cmds, char *oldpwd)
{
	t_env *node;

	node = (t_env *)malloc(sizeof(t_env));
	node->name = "OLDPWD";
	node->value = oldpwd;
	node->next = NULL;
	ft_lstadd_back(&cmds->env, node);
	return (1);
}
//COMPROBAR SI FUNCIONA SI UNSETTEAN El PWD
int change_pwd_and_oldpwd(t_cmds *cmds)
{ 
	char *pwd;
	char *oldpwd;

	pwd = getcwd(NULL, 0);
	oldpwd = get_env_value(cmds, "PWD");
	if (oldpwd != NULL)
	{
		if (change_env_value(cmds, "OLDPWD", oldpwd) == 0)
			create_oldpwd(cmds, oldpwd);
	}
	else
		create_oldpwd(cmds, NULL);
	if (pwd != NULL)
		change_env_value(cmds, "PWD", pwd);
	free(pwd);
	return (1);
} 

int go_to_home(t_cmds *cmds)
{
    char *home;
	int ret;
	
	home = get_env_value(cmds, "HOME");
    if (home == NULL)
    {
        printf("minishell: cd: HOME not set\n");
        return 1;
    }
	ret = chdir(home);
	change_pwd_and_oldpwd(cmds);
    return ret;
}

int go_to_path(t_cmds *cmds, char *path)
{
	int ret;

    if (access(path, F_OK) != 0)
    {
        printf("cd: no such file or directory: %s\n", path);
        return 1;
    }

    if (access(path, R_OK) != 0)
    {
        printf("cd: permission denied: %s\n", path);
        return 1;
    }
	ret = chdir(path);
    return ret;
}

int go_to_previous_directory(t_cmds *cmds)
{
    char *oldpwd;
	int ret;
	
	ret = 0;
	oldpwd = get_env_value(cmds, "OLDPWD");
    if (oldpwd == NULL)
    {
        printf("minishell: cd: OLDPWD not set\n");
        return 1;
    }
	else
		ret = chdir(oldpwd);
    return ret;
}

int go_to_current_directory(t_cmds *cmds)
{
    char *pwd;
	int ret;
	
	pwd = get_env_value(cmds, "PWD");
    if (pwd == NULL)
        return 0;
	ret = chdir(pwd);
	change_pwd_and_oldpwd(cmds);
    return ret;
}

int go_to_parent_directory(t_cmds *cmds)
{
	int ret;
	
	ret = chdir("..");
	change_pwd_and_oldpwd(cmds);
	return ret;
}

int ft_cd(t_cmds *cmds)
{
	if (cmds->opts == NULL || cmds->opts[0] == NULL
		|| ft_strcmp(cmds->opts[0], "~") == 0)
		return go_to_home(cmds);
	else if (ft_strcmp(cmds->opts[0], "..") == 0)
        return go_to_parent_directory(cmds);
    else if (ft_strcmp(cmds->opts[0], "-") == 0)
        return go_to_previous_directory(cmds);
    else if (ft_strcmp(cmds->opts[0], ".") == 0)
        return go_to_current_directory(cmds);
    else
        return go_to_path(cmds, cmds->opts[0]);
}
