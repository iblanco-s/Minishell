/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iblanco- <iblanco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 17:48:44 by iblanco-          #+#    #+#             */
/*   Updated: 2022/09/12 16:31:24 by iblanco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tolower(int ch)
{
	if ((65 <= ch) && (ch <= 90))
		return (ch + 32);
	else
		return (ch);
}

/*int main()
{
    int j = 0;
    char str[] = "GeEks@123\n";
    char ch;
 
    while (str[j]) {
        ch = str[j];
        putchar(toupper(ch));
		printf("\n");
		putchar(toupper(ch));
		printf("\n");
        j++;
    }
 
    return 0;
}*/
