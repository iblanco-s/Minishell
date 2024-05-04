/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iblanco- <iblanco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 18:51:26 by iblanco-          #+#    #+#             */
/*   Updated: 2022/09/13 19:28:07 by iblanco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char	*kdest;
	char	*ksrc;

	kdest = (char *)dest;
	ksrc = (char *)src;
	if (dest == NULL && src == NULL)
		return (0);
	while (n > 0)
	{
		*kdest = *ksrc;
		kdest++;
		ksrc++;
		n--;
	}
	return (dest);
}
