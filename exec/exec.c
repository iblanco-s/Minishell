/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsalaber <jsalaber@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 13:25:14 by junesalaber       #+#    #+#             */
/*   Updated: 2024/04/26 11:26:57 by jsalaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*ft_get_path(char *path, char *cmd)
{
	char	**split_path;
	char	*exec_path;
	char	*part_path;
	int		i;

	if (!path)
		return (NULL);
	split_path = ft_split(path, ':');
	if (!split_path)
		return (NULL);
	i = -1;
	while (split_path[++i])
	{
		part_path = ft_strjoin(split_path[i], "/");
		exec_path = ft_strjoin(part_path, cmd);
		free(part_path);
		if (access(exec_path, F_OK | X_OK) == 0)
			return (ft_free_split(split_path), exec_path);
		free(exec_path);
	}
	ft_free_split(split_path);
	return (NULL);
}

char	*path_value(t_shell *shell)
{
	char	*path_value;

	path_value = get_env_value(shell, "PATH");
	return (path_value);
}

char	**env_to_envp(t_env *env)
{
	char	**envp;
	char	**tmp_envp;
	char	*tmp;

	envp = malloc(sizeof(char *) * (ft_lstsize_tenv(env) + 1));
	tmp_envp = envp;
	while (env)
	{
		tmp = ft_strjoin(env->name, "=");
		*envp = ft_strjoin(tmp, env->value);
		free(tmp);
		envp++;
		env = env->next;
	}
	*envp = NULL;
	return (tmp_envp);
}

void	exec_cmd(t_shell *shell, char **cmd, char *path_value, char **envp)
{
	char	*path;

	if (!*cmd)
		exit (0);
	if (exec_builtin(cmd, shell))
		exit (0);
	if (!ft_strchr(cmd[0], '/'))
		path = ft_get_path(path_value, cmd[0]);
	else if (access(cmd[0], X_OK) == 0)
		path = ft_strdup(cmd[0]);
	else
		path = NULL;
	if (!path)
	{
		ft_putendl_fd("Command not found", 2);
		exit (127);
	}
	if (execve(path, cmd, envp) == -1)
	{
		free(path);
		ft_putendl_fd("Error executing command", 2);
		exit (127);
	}
}

void	manage_exec(t_shell *shell)
{
	if (!shell)
		return ;
	if (shell->cmds && !shell->cmds->next && ft_is_builtin(shell->cmds->opts))
		exec_single_builtin(shell, shell->cmds->opts);
	else
	{
		exec_pipe(shell, shell->cmds, shell->cmds);
	}
		
}
