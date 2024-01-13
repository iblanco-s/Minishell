/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_special_chars.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inigo <inigo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 13:07:09 by inigo             #+#    #+#             */
/*   Updated: 2024/01/13 19:10:57 by inigo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	divide_and_get_char(t_env *token_list, int i)
{
	t_env	*node_after_char;
	t_env	*node_char;

	node_after_char = malloc(sizeof(t_env));
	node_after_char->name = ft_strdup(&token_list->name[i + 1]);
	node_char = malloc(sizeof(t_env));
	node_char->name = malloc(sizeof(char) * 2);
	node_char->name[0] = token_list->name[i];
	node_char->name[1] = '\0';
	node_char->next = node_after_char;
	token_list->name[i] = '\0';
	node_after_char->next = token_list->next;
	token_list->next = node_char;
}

void	check_pipes_and_redirs(t_env *token_list)
{
	int	i;

	i = 0;
	token_list = ft_lstlast(token_list);
	while (token_list->name[i])
	{
		if (token_list->name[i] == '|' || token_list->name[i] == '<'
			|| token_list->name[i] == '>')
		{
			divide_and_get_char(token_list, i);
			if (token_list->next->next)
				token_list = token_list->next;
			break ;
		}
		i++;
	}
}

void	divide_dollar(t_env *token_list, int i)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	node->name = ft_strdup(&token_list->name[i]);
	token_list->name[i] = '\0';
	node->next = token_list->next;
	token_list->next = node;
}

void	split_dollar(t_env *token_list)
{
	int	i;

	i = 0;
	while (token_list)
	{
		if (token_list->name && token_list->name[i] != '$')
		{
			while (token_list->name[++i])
			{
				if (token_list->name[i] == '$')
				{
					divide_dollar(token_list, i);
					if (token_list->next->next)
						token_list = token_list->next;
					break ;
				}
			}
		}
		token_list = token_list->next;
		i = 0;
	}
}
