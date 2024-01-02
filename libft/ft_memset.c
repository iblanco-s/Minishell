/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iblanco- <iblanco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 18:34:01 by iblanco-          #+#    #+#             */
/*   Updated: 2022/09/13 18:37:35 by iblanco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *str, int c, size_t n)
{
	unsigned char	*k;

	k = (unsigned char *)str;
	while (n > 0)
	{
		*k = (unsigned char) c;
		k++;
		n--;
	}
	return (str);
}
