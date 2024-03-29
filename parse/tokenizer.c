/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inigo <inigo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 17:13:39 by inigo             #+#    #+#             */
/*   Updated: 2024/03/29 11:15:02 by inigo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// char	**expander(char **tokenized_line, t_cmds *cmds)
// {
// 	int		i;
// 	char	*value;
//
// 	i = 0;
// 	while (tokenized_line[i])
// 	{
// 		if (tokenized_line[i][0] == '$')
// 		{
// 			value = get_env_value(cmds, &tokenized_line[i][1]);
// 			free(tokenized_line[i]);
// 			if (value)
// 				tokenized_line[i] = ft_strdup(value);
// 			else
// 				tokenized_line[i] = ft_strdup("");
// 		}
// 		i++;
// 	}
// 	return (tokenized_line);
// }
t_env *expander(t_env *env_list, t_cmds *cmds)
{
	t_env *current = env_list;
	char *value;

	while (current)
	{
		if (current->name[0] == '$' && current->single_quote == 0)
		{
			value = get_env_value(cmds, &current->name[1]);
			free(current->name);
			if (value)
				current->name = ft_strdup(value);
			else
				current->name = ft_strdup("");
		}
		current = current->next;
	}
	return env_list;
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

	// Actualmente tras parsear la linea y tener una lista de tokens divida
	// y lista para ejecutar  
	// ex: linea: echo hola  | cat -e -> lista nodo 1: "echo hola", nodo 2: "cat -e"
	// con list to array se convierte en un array de strings, esto no tiene que ser asi
	// dependiendo como hagamos la ejecucion igual nos sigue interesando tenerlo en lista
	tokenized_line = list_to_array(general_split(line, cmds));
	if (!tokenized_line)
		printf("Error\n");
}
