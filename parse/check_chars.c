#include "../minishell.h"

int	search_char(char *str, char c)
{
    int i;

    i = 0;
	while (str[i])
	{
		if (str[i] == c)
		{
			return (1);
		}
		i++;
	}
	return (0);
}

int	special_char(char *str, char c)
{
	if (search_char(str, c))
	{
		printf("Error: I do not interpret the special character %c\n", c);
		return (1);
	}
	return (0);
}

int	forbidden_chars(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
	    if (!ft_isascii(str[i])
           /* && special_char(str[i], '(')
		    && special_char(str[i], ')')
		    && special_char(str[i], '*')
            && special_char(str[i], '`')*/   /* hay que tener en cuenta tambien \\?* o #/
		    && special_char(str[i], ';')
		    && special_char(str, 92));  // 92 es '\' en ascii 	
		        return (1);
        i++;
    }
	return (0);	
}