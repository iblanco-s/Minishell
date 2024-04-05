/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inigo <inigo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 17:13:39 by inigo             #+#    #+#             */
/*   Updated: 2024/04/05 18:30:43 by inigo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/**
 * @brief Junta los tokens que por las comillas se han dividido
 * pero que deberian ir juntos
 * 
 * @param token_list Lista de tokens
*/
void	join_nodes_because_quotes(t_env **token_list)
{
	t_env	*current;
	t_env	*tmp;

	current = *token_list;
	while (current)
	{
		if (current->join_with_quotes == 1)
		{
			if (current->next == NULL)
				break ;
			tmp = current->next;
			current->next = tmp->next;
			current->name = ft_strjoin(current->name, tmp->name);
			if (tmp->join_with_quotes == 1)
			{
				free(tmp->name);
				free(tmp);
				continue ;
			}
			free(tmp->name);
			free(tmp);
		}
		current = current->next;
	}
}

/**
 * @brief Parsea la linea de entrada y la convierte en tokens
 * 
 * @param line Linea de entrada
 * @param cmds Estructura con los env ya obtenidos
 */
void	handle_input(char *line, t_cmds *cmds)
{
	char	**tokenized_line;

	// AQUI TENDRIAMOS QUE LLAMAR A LA FUNCION QUE CHECKEA TODAS LAS TRAMPAS QUE HAY QUE TAPAR
	// EJEMPLO: COMILLAS SIN CERRAR; PIPE AL INICIO; DOBLE PIPE; DOBLE REDIRECCION SEPARADO POR ESPACIO
	// ETC
	// initial_check(line);

	// Actualmente tras parsear la linea y tener una lista de tokens divida
	// y lista para ejecutar  
	// ex: linea: echo hola  | cat -e -> lista nodo 1: "echo hola", nodo 2: "cat -e"
	// con list to array se convierte en un array de strings, esto no tiene que ser asi
	// dependiendo como hagamos la ejecucion igual nos sigue interesando tenerlo en lista
	tokenized_line = list_to_array(general_split(line, cmds));
	if (!tokenized_line)
		printf("Error\n");
}
