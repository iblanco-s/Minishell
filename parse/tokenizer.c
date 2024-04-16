/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inigo <inigo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 17:13:39 by inigo             #+#    #+#             */
/*   Updated: 2024/04/16 23:38:09 by inigo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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
	// initial_check(line);

	general_split(line, shell);
	//builtin_check(tokenized_line, shell);
}
