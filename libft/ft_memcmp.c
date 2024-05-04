/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iblanco- <iblanco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 18:49:14 by iblanco-          #+#    #+#             */
/*   Updated: 2022/09/14 18:59:31 by iblanco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *str1, const void *str2, size_t n)
{
	size_t		i;
	char		*kstr1;
	char		*kstr2;

	i = 0;
	kstr1 = (char *)str1;
	kstr2 = (char *)str2;
	while (i < n)
	{
		if (kstr1[i] != kstr2[i])
			return ((unsigned char)kstr1[i] - (unsigned char)kstr2[i]);
		else if (kstr1[i] == kstr2[i])
			i++;
	}
	return (0);
}
