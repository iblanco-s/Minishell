/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iblanco- <iblanco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 19:54:54 by iblanco-          #+#    #+#             */
/*   Updated: 2022/10/03 16:19:14 by iblanco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*retlist;
	t_list	*temp;	

	if (!lst)
		return (NULL);
	retlist = ft_lstnew(f(lst -> content));
	if (!retlist)
		ft_lstclear(&(retlist), del);
	retlist -> next = NULL;
	temp = retlist;
	lst = lst -> next;
	while (lst)
	{
		temp -> next = ft_lstnew(f(lst->content));
		if (!(temp->next))
			ft_lstclear(&(retlist), del);
		temp = temp -> next;
		temp -> next = NULL;
		lst = lst -> next;
	}
	return (retlist);
}
