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

//#include "../minishell.h"

#include <stdio.h> //printf,
#include <stdlib.h> //exit,

//Comillas dobles y simples sin cerrar o sueltas

char	*search(char *str, char c)
{
	int	i;

	i = 0;
	if (str[i] == c)
	{
		str++;
		while (str[i] != c && str[i])
		{
			printf("print de search: %c\n",str[i]);
			str++;
		}
	}
	return (str);
}

char	*search_quotes(char *str)
{
	printf("print de search_quotes: %s\n",str);
	str = search(str, '"');
	str = search(str, 39);
	return (str);
}

int	check_quotes(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		str = search_quotes(str);
		if (str[i] == 0)
		{
			return (0);
		}
		str++;
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


/*static int	check_content(char *str, char c)
{
	if (special_char(str, c))
	{
		printf("Error: I do not interpret the special character %c\n", c);
		return (0);
	}
	return (1);
} */

/*int	check_forbiden(char *str)
{
	if (check_quotes(str)
		&& check_content(str, '(')
		&& check_content(str, ')')
		&& check_content(str, '*')
		&& check_content(str, ';')
		&& check_content(str, 92));  // 92 es '\' en ascii 	
		return (0);
	return (1);	
}*/

int	main(int argc, char **argv)
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
}
