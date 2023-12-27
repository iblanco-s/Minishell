/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_aux.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iblanco- <iblanco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 17:50:01 by iblanco-          #+#    #+#             */
/*   Updated: 2023/12/27 17:24:06 by iblanco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*get_env_value(t_cmds *cmds, char *name)
{
	t_env	*current;

	current = cmds->env;
	while (current != NULL)
	{
		if (strcmp(current->name, name) == 0)
			return (current->value);
		current = current->next;
	}
	return (NULL);
}

int	create_oldpwd(t_cmds *cmds, char *oldpwd)
{
	t_env	*node;

	node = (t_env *)malloc(sizeof(t_env));
	node->name = "OLDPWD";
	node->value = oldpwd;
	node->next = NULL;
	ft_lstadd_back(&cmds->env, node);
	return (1);
}

int	change_pwd_and_oldpwd(t_cmds *cmds)
{
	char	*pwd;
	char	*oldpwd;

	pwd = getcwd(NULL, 0);
	oldpwd = ft_strdup(get_env_value(cmds, "PWD"));
	if (oldpwd != NULL)
	{
		if (change_env_value(cmds, "OLDPWD", oldpwd) == 0)
			create_oldpwd(cmds, oldpwd);
	}
	else
		create_oldpwd(cmds, NULL);
	if (pwd != NULL)
		change_env_value(cmds, "PWD", pwd);
	//free(pwd);
	return (1);
}

int	go_to_path(t_cmds *cmds, char *path)
{
	int	ret;

	if (access(path, F_OK) != 0)
	{
		printf("minishell: cd: no such file or directory: %s\n", path);
		return (1);
	}
	if (access(path, R_OK) != 0)
	{
		printf("minishell: cd: permission denied: %s\n", path);
		return (1);
	}
	ret = chdir(path);
	change_pwd_and_oldpwd(cmds);
	return (ret);
}
