/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inigo <inigo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 17:22:49 by iblanco-          #+#    #+#             */
/*   Updated: 2022/09/20 17:11:58 by inigo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nitems, size_t size)
{
	void		*mem;

	mem = malloc(nitems * size);
	if (mem == NULL)
		return (0);
	ft_bzero(mem, nitems * size);
	return (mem);
}
