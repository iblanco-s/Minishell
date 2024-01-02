/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iblanco- <iblanco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 17:24:14 by iblanco-          #+#    #+#             */
/*   Updated: 2022/10/03 16:29:50 by iblanco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t len)
{
	size_t	i;
	size_t	k;

	i = 0;
	k = 0;
	while (src[i] != '\0')
		i++;
	if (len > 0)
	{
		while (src[k] != '\0')
		{
			dest[k] = src[k];
			k++;
			if (k == len)
			{
				k--;
				break ;
			}
		}
		dest[k] = '\0';
	}
	return (i);
}
