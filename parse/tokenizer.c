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
	{
		ft_putstr_fd("minishell: Error: unclosed quotes\n", 2);
		return (-1);
	}
	return (1);
}

int	check_pipe_at_start(char *line)
{
	int	i;

	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\"' || line[i] == '\''))
		i++;
	if (line[i] && line[i] == '|')
	{
		ft_putstr_fd("minishell: Error: pipe at start not valid\n", 2);
		return (-1);
	}
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
// test <<< test
// int	check_special_chars(char *line)
// {
// 	int		i;
// 	char	c;

// 	i = 0;
// 	while (line[i])
// 	{
// 		if (line[i] == '<' && line[i + 1] && line[i + 1] == '<')
// 			i++;
// 		else if (line[i] == '>' && line[i + 1] && line[i + 1] == '>')
// 			i++;
// 		else if (line[i] == '<' || line[i] == '>'
// 			|| line[i] == '|')
// 			{
// 				if (line[i + 1] == '\0')
// 				{
// 					ft_putstr_fd("minishell: Error: special char cant be at the end\n", 2);
// 					return (-1);
// 				}
// 				c = get_next_char(&line[i + 1]);
// 				if (c == '\0')
// 				{
// 					ft_putstr_fd("minishell: Error: special char must be followed by something\n", 2);
// 					return (-1);
// 				}
// 				else if (c == '<' || c == '>'
// 					|| c == '|')
// 				{
// 					ft_putstr_fd("minishell: Error: special char cant be followed by another special char\n", 2);
// 					return (-1);
// 				}
// 			}
// 		i++;
// 	}
// 	return (1);
// }

int	initial_filter(char *line)
{
	if (line == NULL || line[0] == '\0')
		return (-1);
	if (check_unclosed_quotes(line) == -1)
		return (-1);
	if (check_pipe_at_start(line) == -1)
		return (-1);
	// if (check_special_chars(line) == -1)
	// 	return (-1);
	return (1);
}

/**
 * @brief Parsea la linea de entrada y la convierte en tokens
 * 
 * @param line Linea de entrada
 * @param cmds Estructura con los env ya obtenidos
 */
void	handle_input(char *line, t_shell *shell)
{
	//char	**tokenized_line;

	// AQUI TENDRIAMOS QUE LLAMAR A LA FUNCION QUE CHECKEA TODAS LAS TRAMPAS QUE HAY QUE TAPAR
	// EJEMPLO: COMILLAS SIN CERRAR; PIPE AL INICIO; DOBLE PIPE; DOBLE REDIRECCION SEPARADO POR ESPACIO
	// ETC
	// contra muchos espacios o salto de linea pasa algo si entra en el bucle?
	if (initial_filter(line) == -1)
		return ;
	general_split(line, shell);
	// builtin_check(tokenized_line, shell);
}
