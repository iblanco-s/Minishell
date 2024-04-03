/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_special_chars.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inigo <inigo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 13:07:09 by inigo             #+#    #+#             */
/*   Updated: 2024/04/03 18:13:18 by inigo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//"testing: echo \"hello > world\" | cat echo \"hello > world\" > 
//cat hola > adios hola >> adios hola > adios hola >> adios hola> 
//adios hola >adios hola>adios hola>>adios hola<< adios hola <<adios"

void	divide_and_get_char(t_env *token_list, int i,
	int char_num, t_env	*node_after_char)
{
	t_env	*node_with_char;

	node_with_char = NULL;
	if (token_list->name[i + char_num])
	{
		node_after_char = malloc(sizeof(t_env));
		node_after_char->name = ft_strdup(&token_list->name[i + char_num]);
		node_after_char->single_quote = token_list->single_quote;
		token_list->name[i + char_num] = '\0';
		node_after_char->next = token_list->next;
		token_list->next = node_after_char;
	}
	if (i > 0)
	{
		node_with_char = malloc(sizeof(t_env));
		node_with_char->name = ft_strdup(&token_list->name[i]);
		node_with_char->single_quote = token_list->single_quote;
		token_list->name[i] = '\0';
		if (node_after_char)
			node_with_char->next = node_after_char;
		else
			node_with_char->next = token_list->next;
		token_list->next = node_with_char;
	}
}

/**
 * @brief Check if there are pipes or redirections in the input
 * and divide them into different nodes
 * 
 * @param token_list to check
*/
void	check_pipes_and_redirs(t_env *token_list)
{
	int	i;

	i = 0;
	token_list = ft_lstlast(token_list);
	while (token_list->name[i])
	{
		if (token_list->name[i] == '|')
		{
			if (i > 0 || token_list->name[i + 1])
				divide_and_get_char(token_list, i, 1, NULL);
		}
		else if (token_list->name[i] == '<' || token_list->name[i] == '>')
		{
			if (token_list->name[i + 1] && token_list->name[i + 1]
				== token_list->name[i])
			{
				divide_and_get_char(token_list, i, 2, NULL);
				i++;
			}
			else if (i > 0 || token_list->name[i + 1])
				divide_and_get_char(token_list, i, 1, NULL);
		}
		i++;
	}
}
