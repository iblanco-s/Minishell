/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_special_chars.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inigo <inigo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 13:07:09 by inigo             #+#    #+#             */
/*   Updated: 2024/04/15 21:21:22 by inigo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//"testing: echo \"hello > world\" | cat echo \"hello > world\" > 
//cat hola > adios hola >> adios hola > adios hola >> adios hola> 
//adios hola >adios hola>adios hola>>adios hola<< adios hola <<adios"

void	divide_and_get_char(t_parse *token_list, int i,
	int char_num, t_parse *node_after_char)
{
	t_parse	*node_with_char;

	node_with_char = NULL;
	if (token_list->token[i + char_num])
	{
		node_after_char = malloc(sizeof(t_parse));
		node_after_char->token = ft_strdup(&token_list->token[i + char_num]);
		node_after_char->quote = token_list->quote;
		token_list->token[i + char_num] = '\0';
		node_after_char->next = token_list->next;
		token_list->next = node_after_char;
	}
	if (i > 0)
	{
		node_with_char = malloc(sizeof(t_parse));
		node_with_char->token = ft_strdup(&token_list->token[i]);
		node_with_char->quote = token_list->quote;
		token_list->token[i] = '\0';
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
void	check_pipes_and_redirs(t_parse *token_list)
{
	int	i;

	i = 0;
	token_list = ft_lstlast_parse(token_list);
	while (token_list->token[i])
	{
		if (token_list->token[i] == '|')
		{
			if (i > 0 || token_list->token[i + 1])
				divide_and_get_char(token_list, i, 1, NULL);
		}
		else if (token_list->token[i] == '<' || token_list->token[i] == '>')
		{
			if (token_list->token[i + 1] && token_list->token[i + 1]
				== token_list->token[i])
			{
				divide_and_get_char(token_list, i, 2, NULL);
				i++;
			}
			else if (i > 0 || token_list->token[i + 1])
				divide_and_get_char(token_list, i, 1, NULL);
		}
		i++;
	}
}
