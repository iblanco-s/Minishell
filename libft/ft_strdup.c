/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iblanco- <iblanco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 17:56:33 by iblanco-          #+#    #+#             */
/*   Updated: 2022/09/19 19:08:26 by iblanco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*ret;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (s[i] != '\0')
		i++;
	ret = ((char *) malloc((i + 1) * sizeof(char)));
	if (ret == NULL)
		return (0);
	while (j < i)
	{
		ret[j] = s[j];
		j++;
	}
	ret[j] = '\0';
	return (ret);
}
