/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iblanco- <iblanco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 15:59:02 by iblanco-          #+#    #+#             */
/*   Updated: 2022/09/14 18:16:19 by iblanco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*kdest;
	char	*ksrc;
	size_t	i;

	kdest = (char *)dest;
	ksrc = (char *)src;
	i = 0;
	if (dest == NULL && src == NULL)
		return (0);
	while ((ksrc != (void *)0 || kdest != (void *)0) && i < n)
	{
		if (src < dest)
			kdest[n - i - 1] = ksrc[n - i - 1];
		else
			kdest[i] = ksrc[i];
		i++;
	}
	return (dest);
}
/*si vas hacia atras no necesitas hacer un char * temporal (linea 26-29)*/