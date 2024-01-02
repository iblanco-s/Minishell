/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iblanco- <iblanco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 11:30:10 by inigo             #+#    #+#             */
/*   Updated: 2022/09/19 19:08:37 by iblanco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t		i;
	size_t		j;
	size_t		k;
	char		*ret;

	i = ft_strlen(s1);
	j = ft_strlen(s2);
	k = 0;
	ret = (malloc((i + j + 1) * sizeof(char)));
	if (ret == NULL)
		return (0);
	j = 0;
	while (s1[k] != '\0')
	{
		ret[k] = s1[k];
		k++;
	}
	while (s2[j] != '\0')
	{
		ret[k] = s2[j];
		k++;
		j++;
	}
	ret[k] = '\0';
	return (ret);
}
