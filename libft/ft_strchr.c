+/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iblanco- <iblanco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 17:26:58 by iblanco-          #+#    #+#             */
/*   Updated: 2022/09/14 18:36:39 by iblanco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	int	i;

	i = 0;
	if (str[0] == '\0')
	{
		if (c == '\0')
			return ((char *)&str[0]);
	}
	while (str[i] != '\0')
	{
		if (str[0] == (char)c)
			return ((char *)&str[0]);
		i++;
		if (str[i] == (char)c)
			return ((char *)&str[i]);
	}
	return (0);
}
