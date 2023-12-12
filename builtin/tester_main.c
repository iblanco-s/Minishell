/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tester_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iblanco- <iblanco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 18:49:44 by iblanco-          #+#    #+#             */
/*   Updated: 2023/12/12 18:58:27 by iblanco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <stdlib.h>

//funcion que separa el env entre value y name

t_env *ft_env1(char **env)
{
    t_env *head = NULL;
    t_env *current = NULL;

    for (int i = 0; env[i] != NULL; i++)
    {
        t_env *node = malloc(sizeof(t_env));
        char *equal_sign = strchr(env[i], '=');
        if (equal_sign != NULL)
        {
            int name_length = equal_sign - env[i];
            node->name = strndup(env[i], name_length);
            node->value = strdup(equal_sign + 1);
        }
        else
        {
            node->name = strdup(env[i]);
            node->value = NULL;
        }

        node->next = NULL;

        if (head == NULL)
        {
            head = node;
            current = node;
        }
        else
        {
            current->next = node;
            current = node;
        }
    }

    return head;
}

int main(int argc, char **argv, char **env)
{
    t_cmds *cmds = malloc(sizeof(t_cmds));
    argc = 0;
    argv = NULL;

    // Initialize cmds->env and cmds->opts as NULL for now
    cmds->env = ft_env1(env);
    cmds->opts = NULL;

    ft_pwd(cmds);

    // Test ft_export
    char *opts[] = {"JODER=1", NULL};
    cmds->opts = opts;
    ft_export(cmds);

    // Test ft_env
    ft_env(cmds);
	
    // Test ft_unset
    char *unset_opts[] = {"JODER", NULL};
    cmds->opts = unset_opts;
    ft_unset(cmds);

    // Test ft_env
    ft_env(cmds);
	
    // Test ft_export with non-alpha characters
    char *non_alpha_opts[] = {"123=1", NULL};
    cmds->opts = non_alpha_opts;
    ft_export(cmds);

    char *non_alpha_opts1[] = {"=1231", NULL};
    cmds->opts = non_alpha_opts1;
    ft_export(cmds);
	
    free(cmds);
    return 0;
}