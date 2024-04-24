/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsalaber <jsalaber@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 17:13:39 by inigo             #+#    #+#             */
/*   Updated: 2024/04/22 11:58:20 by jsalaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// Check for unclosed quotes " or '
int	check_unclosed_quotes(char *line)
{
	int	quote_simple;
	int	quote_double;
	int	i;

	quote_simple = 0;
	quote_double = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == '\"' && quote_double != 1)
			quote_double = 1;
		else if (line[i] == '\'' && quote_simple != 2)
			quote_simple = 2;
		else if (line[i] == '\"' && quote_double == 1)
			quote_double = 0;
		else if (line[i] == '\'' && quote_simple == 2)
			quote_simple = 0;
		i++;
	}
	if (quote_double != 0 || quote_simple != 0)
		return (print_error_and_return(UNCLOSED_QUOTES_ERROR));
	return (1);
}

int	check_pipe_at_start(char *line)
{
	int	i;

	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\"' || line[i] == '\''))
		i++;
	if (line[i] && line[i] == '|')
		return (print_error_and_return(PIPE_AT_START_ERROR));
	return (1);
}

char	get_next_char(char *line)
{
	int	i;

	i = 0;
	while (line[i] && (line[i] == ' '))
		i++;
	if (line[i] == '\0')
		return ('\0');
	return (line[i]);
}

int	initial_filter(char *line)
{
	if (line == NULL || line[0] == '\0')
		return (print_error_and_return(EMPTY_LINE_ERROR));
	if (!check_unclosed_quotes(line))
		return (0);
	if (!check_pipe_at_start(line))
		return (0);
	if (!check_special_chars(line))
		return (0);
	return (1);
}

/**
 * @brief Parsea la linea de entrada y la convierte en tokens
 * 
 * @param line Linea de entrada
 * @param cmds Estructura con los env ya obtenidos
 */
int	handle_input(char *line, t_shell *shell)
{
	if (!initial_filter(line))
		return (0);
	general_split(line, shell);
	return (1);
}
