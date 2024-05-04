/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iblanco- <iblanco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 19:40:27 by iblanco-          #+#    #+#             */
/*   Updated: 2022/09/13 17:53:54 by iblanco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char	*str1, const char *str2, size_t len)
{
	size_t	i;
	size_t	j;
	char	*str0;

	i = 0;
	str0 = (char *)str1;
	if (str2[0] == '\0')
		return (str0);
	while (str1[i] != '\0' && i < len)
	{
		j = 0;
		while (str1[i + j] == str2[j] && str1[i + j] != '\0' && i + j < len)
		{
			if (str2[j + 1] == '\0')
				return (&str0[i]);
			j++;
		}
		i++;
	}
	return (0);
}
