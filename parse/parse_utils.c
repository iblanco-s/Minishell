/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inigo <inigo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 20:49:37 by inigo             #+#    #+#             */
/*   Updated: 2024/04/21 19:50:24 by inigo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_lstsize_parse(t_parse *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		lst = lst -> next;
		i++;
	}
	return (i);
}

t_parse	*ft_lstlast_parse(t_parse *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	ft_lstadd_back_parse(t_parse **lst, t_parse *new)
{
	if (!*lst)
		*lst = new;
	else
		ft_lstlast_parse(*lst)->next = new;
}

void	delete_empty_nodes(t_parse **token_list)
{
	t_parse	*current;
	t_parse	*tmp;

	current = *token_list;
	while (current)
	{
		if (current->next && current->next->token == NULL)
		{
			tmp = current->next;
			if (current->next->next)
				current->next = current->next->next;
			else
				current->next = NULL;
			free(tmp);
		}
		current = current->next;
	}
}
