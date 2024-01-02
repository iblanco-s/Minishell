/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iblanco- <iblanco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 18:17:41 by iblanco-          #+#    #+#             */
/*   Updated: 2022/09/14 18:55:14 by iblanco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *str, int c, size_t n)
{
	int				i;
	unsigned char	*kstr;

	i = 0;
	kstr = (unsigned char *)str;
	while (n > 0)
	{
		if (kstr[i] == (unsigned char)c)
			return ((char *)&str[i]);
		i++;
		n--;
	}
	return (0);
}
