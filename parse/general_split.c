/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inigo <inigo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 13:06:00 by inigo             #+#    #+#             */
/*   Updated: 2024/04/16 23:37:04 by inigo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/**
 * @brief Junta los tokens que por las comillas se han dividido
 * pero que deberian ir juntos
 * 
 * @param token_list Lista de tokens
*/
void	join_nodes_because_quotes(t_parse **token_list)
{
	t_parse	*current;
	t_parse	*tmp;

	current = *token_list;
	while (current)
	{
		if (current->join_with_quotes == 1)
		{
			if (current->next == NULL)
				break ;
			tmp = current->next;
			current->next = tmp->next;
			current->token = ft_strjoin(current->token, tmp->token);
			if (tmp->join_with_quotes == 1)
			{
				free(tmp->token);
				free(tmp);
				continue ;
			}
			free(tmp->token);
			free(tmp);
		}
		current = current->next;
	}
}

t_parse	*get_next_word(char **line)
{
	int		i;
	t_parse	*node;

	node = malloc(sizeof(t_parse));
	i = 0;
	while ((*line)[i] && (*line)[i] != ' '
		&& (*line)[i] != '\"' && (*line)[i] != '\'')
		i++;
	if ((*line)[i] == '\"' || (*line)[i] == '\'')
		node->join_with_quotes = 1;
	else
		node->join_with_quotes = 0;
	node->token = ft_strndup(*line, i - 1);
	node->quote = 0;
	node->next = NULL;
	*line += i;
	return (node);
}

t_parse	*get_next_quote(char **line, int quote, char quote_type)
{
	int		i;
	t_parse	*node;

	node = malloc(sizeof(t_parse));
	i = 0;
	*line += 1;
	while ((*line)[i] && ((*line)[i] != quote_type || (*line)[i - 1] == '\\'))
		i++;
	node->token = ft_strndup(*line, i - 1); //TODO: FUNCION QUE QUITA LAS \ cuando hay " o '
	node->next = NULL;
	node->quote = quote;
	if ((*line)[i + 1] && (*line)[i + 1] != ' ')
		node->join_with_quotes = 1;
	else
		node->join_with_quotes = 0;
	*line += i + 1;
	return (node);
}

/**
 * @brief Primer paso del parseo, quitamos espacios
 * y comillas, tenemos en cuenta pipes, redirecciones
 * y fuera del bucle expandimos los $
 * 
 * @param line Linea de entrada
 * @param cmds Estructura con los env ya obtenidos
 * 
 * @return t_env* Lista con la linea parseada
*/
t_parse	*general_split(char *line, t_shell *shell)
{
	t_parse	*token_list;

	token_list = NULL;
	while (*line)
	{
		while (*line == ' ')
			line++;
		if (*line == '\"')
			ft_lstadd_back_parse(&token_list, get_next_quote(&line, 2, '\"'));
		else if (*line == '\'')
			ft_lstadd_back_parse(&token_list, get_next_quote(&line, 1, '\''));
		else if (*line)
		{
			ft_lstadd_back_parse(&token_list, get_next_word(&line));
			//TODO: DEBEMOS TENER EN CUENTA || = Command Chaining? ZONA GRIS, NO SE INDICA EN NINGUN LADO
			check_pipes_and_redirs(token_list);
		}
	}
	// from echo hola$USER -> echo holaINIGO
	split_dollar(token_list, shell);
	// join nodes depending on flag join_with_quotes
	join_nodes_because_quotes(&token_list);
	// from "echo holaINIGO | cat -e" -> nodo 1: "echo holaINIGO", nodo 2: "cat -e"
	group_by_pipes_and_redirs(shell, &token_list);
	return (token_list);
}
