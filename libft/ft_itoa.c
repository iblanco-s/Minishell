/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iblanco- <iblanco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 12:19:10 by inigo             #+#    #+#             */
/*   Updated: 2022/09/26 17:28:29 by iblanco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_min_int(char *str)
{
	str = malloc(sizeof(char) * (12));
	if (!str)
		return (NULL);
	ft_memcpy(str, "-2147483648", 12);
	return (str);
}

static char	*ft_putnbr(int n, char *str, int *inum)
{
	if (n >= 10)
	{
		ft_putnbr(n / 10, str, inum);
		ft_putnbr(n % 10, str, inum);
	}
	if (n < 10)
	{
		str[*inum] = n + 48;
		*inum += 1;
	}
	return (str);
}

static int	ft_count2(int n)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (n < 0)
	{
		count++;
		n *= -1;
	}
	i = n;
	if (i == 0)
		count++;
	while (i > 0)
	{
		i = i / 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	int		inum;
	char	*str;

	inum = 0;
	str = 0;
	if (n == -2147483648)
		return (ft_min_int(str));
	str = malloc(sizeof(char) * (ft_count2(n) + 1));
	if (!str)
		return (NULL);
	if (n < 0)
	{
		n *= -1;
		str[inum] = '-';
		inum++;
	}
	ft_putnbr(n, str, & inum);
	str[inum] = '\0';
	return (str);
}
