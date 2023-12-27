/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tester_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iblanco- <iblanco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 18:49:44 by iblanco-          #+#    #+#             */
/*   Updated: 2023/12/27 20:17:16 by iblanco-         ###   ########.fr       */
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

	// printf("Testing ft_unset with \"HOLAAAA\"\n\n");
    // char *unset_opts[] = {"HOLAAAA", NULL};
    // cmds->opts = unset_opts;
    // ft_unset(cmds);

    // printf("Testing ft_export with non-alpha characters\n\n");
    // char *non_alpha_opts[] = {"=1", NULL};
    // cmds->opts = non_alpha_opts;
    // ft_export(cmds);

    // printf("Testing ft_export with \"lol=\"\n\n");
    // char *non_alpha_opts1[] = {"lol=", NULL};
    // cmds->opts = non_alpha_opts1;
    // ft_export(cmds);

    // printf("Testing ft_export with \"jjjj=4\"\n\n");
    // char *non_alpha_opts4[] = {"jjjj=4", NULL};
    // cmds->opts = non_alpha_opts4;
    // ft_export(cmds);

    // printf("Testing ft_export with \"TEST111=\"\n\n");
    // char *non_alpha_opts41[] = {"TEST111=", NULL};
    // cmds->opts = non_alpha_opts41;
    // ft_export(cmds);

    // printf("Testing ft_env\n\n");
    // ft_env(cmds);

    // printf("Testing ft_echo with \"Hello\" and \"World\"\n\n");
    // char *opts211[] = {"Hello", "World", NULL};
    // cmds->opts = opts211;
    // ft_echo(cmds);

    // printf("Testing ft_echo with \"-n\", \"Hello\", and \"World\"\n\n");
    // char *opts3[] = {"-n", "Hello", "World", NULL};
    // cmds->opts = opts3;
    // ft_echo(cmds);

    // printf("Testing ft_echo with \"-nnnnnn\", \"Hello\", and \"World\"\n\n");
    // char *opts4[] = {"-nnnnnn", "Hello", "World", NULL};
    // cmds->opts = opts4;
    // ft_echo(cmds);

    // printf("Testing ft_echo with \"-nnnnnnnna\", \"Hello\", and \"World\"\n\n");
    // char *opts5[] = {"-nnnnnnnna", "Hello", "World", NULL};
    // cmds->opts = opts5;
    // ft_echo(cmds);

    // printf("Testing ft_exit with one non-numeric argument\n\n");
    // char *opts21[] = {"abc", NULL};
    // cmds->opts = opts21;
    // assert(ft_exit(cmds) == 255);
	ft_pwd();
	printf("\n");
    printf("Testing ft_cd with no arguments (should go to home)\n");
    assert(ft_cd(cmds) == 0);
	ft_pwd();
		printf("\n");
    printf("Testing ft_cd with \"~\" (should go to home)\n");
    char *cd_opts_home[] = {"~", NULL};
    cmds->opts = cd_opts_home;
    assert(ft_cd(cmds) == 0);
ft_pwd();
	printf("\n");
    printf("Testing ft_cd with \"..\" (should go to parent directory)\n");
    char *cd_opts_parent[] = {"..", NULL};
    cmds->opts = cd_opts_parent;
    assert(ft_cd(cmds) == 0);
ft_pwd();
	printf("\n");
    printf("Testing ft_cd with \"-\" (should go to previous directory)\n");
    char *cd_opts_prev[] = {"-", NULL};
    cmds->opts = cd_opts_prev;
    assert(ft_cd(cmds) == 0);
ft_pwd();
	printf("\n");
    printf("Testing ft_cd with \".\" (should stay in the current directory)\n");
    char *cd_opts_current[] = {".", NULL};
    cmds->opts = cd_opts_current;
    assert(ft_cd(cmds) == 0);
ft_pwd();
	printf("\n");
    printf("Testing ft_cd with a valid path (should go to the specified path)\n");
    char *cd_opts_path[] = {"/Users/iblanco-/Desktop/Minishell", NULL};
    cmds->opts = cd_opts_path;
    assert(ft_cd(cmds) == 0);
ft_pwd();
	printf("\n");
    printf("Testing ft_cd with an invalid path (should print an error message)\n");
    char *cd_opts_invalid[] = {"invalid/path", NULL};
    cmds->opts = cd_opts_invalid;
    assert(ft_cd(cmds) == 1);
ft_pwd();
	printf("\n");
    printf("Testing ft_cd with no HOME environment variable set (should print an error message)\n");
    char *unset_opts[] = {"HOME", "OLDPWD", NULL};
    cmds->opts = unset_opts;
	ft_env(cmds);
    ft_unset(cmds);
	ft_env(cmds);
	char *cd_opts_no_home[] = {NULL};
    cmds->opts = cd_opts_no_home;
    ft_cd(cmds);
	
	//     printf("Testing ft_exit with too many arguments\n\n");
    // char *opts31[] = {"123", "456", NULL};
    // cmds->opts = opts31;
    // assert(ft_exit(cmds) == 1);

    // printf("Testing ft_exit with no arguments\n\n");
    // cmds->opts = NULL;
    // assert(ft_exit(cmds) == 0);

    // printf("Testing ft_exit with one numeric argument\n\n");
    // char *exit_opts_numeric[] = {"123", NULL};
    // cmds->opts = exit_opts_numeric;
    // assert(ft_exit(cmds) == 123);
	
	// Test ft_pwd
	ft_pwd();
	//free env
	while (cmds->env)
	{
		t_env *tmp = cmds->env;
		cmds->env = cmds->env->next;
		free(tmp->name);
		free(tmp->value);
		free(tmp);
	}
	free (cmds);
	return 0;
}