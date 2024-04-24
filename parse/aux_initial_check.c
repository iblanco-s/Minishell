/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_initial_check.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inigo <inigo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 18:25:08 by inigo             #+#    #+#             */
/*   Updated: 2024/04/23 19:31:16 by inigo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	print_error_and_return(char *error_message)
{
	ft_putstr_fd(error_message, 2);
	return (0);
}

int	is_special_char(char c)
{
	return (c == '<' || c == '>' || c == '|');
}

int	check_consecutive_special_chars(char *line, int i)
{
	if (line[i] == '|' && line[i + 1] && line[i + 1] == '|')
		return (print_error_and_return(CONSECUTIVE_PIPES_ERROR));
	return (1);
}

int	check_special_char_error(char *line, int i)
{
	char	c;

	if (!line[i + 1] || line[i + 1] == '\0')
		return (print_error_and_return(SPECIAL_CHAR_AT_END_ERROR));
	if (line[i] == '<' && line[i + 1] == '<')
		i++;
	if (line[i] == '>' && line[i + 1] == '>')
		i++;
	c = get_next_char(&line[i + 1]);
	if (c == '\0' || is_special_char(c))
		return (print_error_and_return(SPECIAL_CHAR_PARAM_ERROR));
	return (1);
}

int	check_special_chars(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (is_special_char(line[i]))
		{
			if (!check_consecutive_special_chars(line, i)
				|| !check_special_char_error(line, i))
				return (0);
			if ((line[i] == '<' && line[i + 1] == '<')
				|| (line[i] == '>' && line[i + 1] == '>'))
				i++;
		}
		i++;
	}
	return (1);
}
