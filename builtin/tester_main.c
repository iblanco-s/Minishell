/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tester_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iblanco- <iblanco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 18:49:44 by iblanco-          #+#    #+#             */
/*   Updated: 2023/12/14 17:44:29 by iblanco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <stdlib.h>

// funcion que separa el env entre value y name

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
	argc++;
	argv++;

	// Initialize cmds->env and cmds->opts as NULL for now
	cmds->env = ft_env1(env);
	cmds->opts = NULL;

	// ft_pwd(cmds);

	// // Test ft_unset
	// char *unset_opts[] = {"HOLAAAA", NULL};
	// cmds->opts = unset_opts;
	// ft_unset(cmds);

	// // Test ft_export with non-alpha characters
	// char *non_alpha_opts[] = {"=1", NULL};
	// cmds->opts = non_alpha_opts;
	// ft_export(cmds);

	// char *non_alpha_opts1[] = {"lol=", NULL};
	// cmds->opts = non_alpha_opts1;
	// ft_export(cmds);

	// char *non_alpha_opts4[] = {"jjjj=4", NULL};
	// cmds->opts = non_alpha_opts4;
	// ft_export(cmds);

	// char *non_alpha_opts41[] = {"TEST111=", NULL};
	// cmds->opts = non_alpha_opts41;
	// ft_export(cmds);

	// ft_env(cmds);

	// char *opts2[] = {"Hello", "World", NULL};
	// cmds->opts = opts2;
	// ft_echo(cmds);

	// char *opts3[] = {"-n", "Hello", "World", NULL};
	// cmds->opts = opts3;
	// ft_echo(cmds);

	// char *opts4[] = {"-nnnnnn", "Hello", "World", NULL};
	// cmds->opts = opts4;
	// ft_echo(cmds);

	// char *opts5[] = {"-nnnnnnnna", "Hello", "World", NULL};
	// cmds->opts = opts5;
	// ft_echo(cmds);
	
    // Test ft_exit with one non-numeric argument
    // char *opts2[] = {"abc", NULL};
    // cmds->opts = opts2;
    // assert(ft_exit(cmds) == 255);

    // Test ft_exit with too many arguments
    char *opts3[] = {"123", "456", NULL};
    cmds->opts = opts3;
    assert(ft_exit(cmds) == 1);
	
    // Test ft_exit with no arguments
    // cmds->opts = NULL;
    // assert(ft_exit(cmds) == 0);

    // Test ft_exit with one numeric argument
    // char *opts1[] = {"123", NULL};
    // cmds->opts = opts1;
    // assert(ft_exit(cmds) == 123);
	
	free(cmds);
	return 0;
}