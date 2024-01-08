/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obtain_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inigo <inigo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 17:15:43 by inigo             #+#    #+#             */
/*   Updated: 2024/01/05 17:16:06 by inigo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int find_equal_sign(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (i);
		i++;
	}
	return (-1);
}

void create_node(t_env **head, char *env_value)
{
	t_env *node;
	int equal_sign;

	equal_sign = find_equal_sign(env_value);
	if (equal_sign > 0)
	{
		node = malloc(sizeof(t_env));
		node->name = ft_strndup(env_value, equal_sign - 1);
		node->value = ft_strdup(&env_value[equal_sign + 1]);
		node->next = NULL;
		if (*head == NULL)
			*head = node;
		else
			ft_lstadd_back(head, node);
	}
}

t_env *env_to_list(char **env)
{
	t_env *head = NULL;
	int i;

	i = 0;
	while (env[i])
	{
		create_node(&head, env[i]);
		i++;
	}
	return head;
}