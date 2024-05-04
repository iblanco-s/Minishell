/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_aux.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inigo <inigo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 17:50:01 by iblanco-          #+#    #+#             */
/*   Updated: 2024/04/14 20:10:03 by inigo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*get_env_value(t_shell *shell, char *name)
{
	t_env	*current;

	current = shell->env;
	while (current != NULL)
	{
		if (!current->name || current->local == 0)
		{
			current = current->next;
			continue ;
		}
		if (ft_strcmp(current->name, name) == 0)
			return (ft_strdup(current->value));
		current = current->next;
	}
	return (NULL);
}

int	create_oldpwd(t_shell *shell, char *oldpwd)
{
	t_env	*node;

	node = (t_env *)malloc(sizeof(t_env));
	node->name = "OLDPWD";
	node->value = oldpwd;
	node->next = NULL;
	ft_lstadd_back(&shell->env, node);
	return (1);
}

int	change_pwd_and_oldpwd(t_shell *shell)
{
	char	*pwd;
	char	*oldpwd;

	pwd = getcwd(NULL, 0);
	oldpwd = ft_strdup(get_env_value(shell, "PWD"));
	if (oldpwd != NULL)
	{
		if (change_env_value(shell, "OLDPWD", oldpwd) == 0)
			create_oldpwd(shell, oldpwd);
	}
	else
		create_oldpwd(shell, NULL);
	if (pwd != NULL)
		change_env_value(shell, "PWD", pwd);
	return (1);
}

int	go_to_path(t_shell *shell, char *path)
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
	change_pwd_and_oldpwd(shell);
	return (ret);
}
