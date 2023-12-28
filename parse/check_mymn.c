#include "../minishell.h"

int	last(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		i++;
	}
	i--;
	while (str[i] == ' ' && i > 0)
	{
		i--;
	}
	if (str[i] == '<' || str[i] == '>')
	{
		ft_printf("Error: The <<<>>> can`t got at the end.\n");
		return (1);
	}
	return (0);
}

int	alone(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		while ((str[i] != '<' && str[i] != '>') && str[i])
			i += 1 + search_quotes(str + i) - (str + i);
		if (str[i])
			i++;
		if (str[i] == str[i - 1])
			i++;
		while (str[i] == ' ' && str[i])
			i++;
		if ((str[i] == '<' || str[i] == '>') && str[i])
		{
			printf("Error: Don't put more than one >>><<< followed.\n");
			return (0);
		}
	}
	return (1);
}

int check_mymn(char *str)
{
	if (!last(str) && alone(str));
		return (0);
	return (1);
}