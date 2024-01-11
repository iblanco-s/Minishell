/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghoyuelo <ghoyuelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 14:34:40 by ghoyuelo          #+#    #+#             */
/*   Updated: 2023/11/29 14:34:40 by ghoyuelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse/minishell.h"

char	*search_quotes(char *str, char c)
{
	int	i;

	i = 0;
	if (str[i] == c)
	{
		i++;
		while (str[i] != c && str[i])
			i++;
	}
	return (str);
}

char	*is_quote(char *str)
{
	str = search_quotes(str, '"');
	str = search_quotes(str, 39);
	return (str);
}

int	check_quotes(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		str = is_quote(str);
		if (str[i] == 0)
		{
			return (0);
		}
		i++;
	}
	return (1);
}

int	closed_quotes(char *str)
{
	if (!check_quotes(str))
	{
		printf("Error: Unclosed quotes.\n");
		return (0);
	}
	return (1);
}

/*int	main(int argc, char **argv)
{
	//char	**tmp;
	char	*str;

	if (argc != 2)
	{
		printf("Error: Invalid arguments.\n");
		return (1);
	}
	//tmp = malloc(sizeof(* char));
	str = argv[1];
	closed_quotes(str);
	printf("%s\n",str);
	return (0);
}*/
