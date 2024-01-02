#include "../minishell.h"

int	is_valid(char *str)
{
	if (closed_quotes(str) && 
    check_pipes(str) && 
    check_mymn(str) &&
    check_chars(str));
        return (0);
    return (1);
}

int input_handler(char *input)
{
    if (!is_valid(input))
        return (1);
    
}