/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iblanco- <iblanco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 17:22:18 by iblanco-          #+#    #+#             */
/*   Updated: 2022/09/13 16:34:54 by iblanco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t len)
{
	size_t	idest;
	size_t	isrc;
	size_t	x;
	size_t	z;

	idest = 0;
	isrc = 0;
	x = 0;
	z = 0;
	while (dest[idest] != '\0')
		idest++;
	while (src[isrc] != '\0')
		isrc++;
	if (len <= idest)
		return (len + isrc);
	x = idest;
	while (x + 1 < len && src[z] != '\0')
	{
		dest[x] = src[z];
		x++;
		z++;
	}
	dest[x] = '\0';
	return (idest + isrc);
}
