/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   group_by_pipes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inigo <inigo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 10:31:59 by inigo             #+#    #+#             */
/*   Updated: 2024/04/03 18:22:45 by inigo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	free_list(t_env *list)
{
	t_env	*tmp;

	while (list)
	{
		tmp = list;
		list = list->next;
		free(tmp->name);
		free(tmp);
	}
}

t_env	*create_new_node(void)
{
	t_env	*new_node;

	new_node = malloc(sizeof(t_env));
	new_node->name = NULL;
	new_node->single_quote = 0;
	new_node->next = NULL;
	return (new_node);
}

void	append_to_node(t_env *node, char *content)
{
	char	*tmp;

	if (node->name)
	{
		tmp = node->name;
		node->name = ft_strjoin(node->name, " ");
		free(tmp);
		tmp = node->name;
		node->name = ft_strjoin(node->name, content);
		free(tmp);
	}
	else
		node->name = ft_strdup(content);
}

void	group_by_pipes(t_env **token_list)
{
	t_env	*current;
	t_env	*new_list;
	t_env	*new_current;

	current = *token_list;
	new_list = create_new_node();
	new_current = new_list;
	while (current)
	{
		// DAMOS POR HECHO QUE NO PUEDE METER UN PIPE AL PRINCIPIO (LO CHECKEAMOS EN EL INICIO INICIO)
		// Y AL FINAL TAMPOCO  PUEDE PORQUE SALTA EL QUOTE <
		if (current->name[0] == '|' && current->name[1] == '\0')
		{
			new_current->next = create_new_node();
			new_current = new_current->next;
		}
		else
			append_to_node(new_current, current->name);
		current = current->next;
	}
	free_list(*token_list);
	*token_list = new_list;
}
