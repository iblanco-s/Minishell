/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inigo <inigo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 13:06:00 by inigo             #+#    #+#             */
/*   Updated: 2024/04/21 18:15:38 by inigo            ###   ########.fr       */
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
		if (current->join_with_quotes && current->join_with_quotes == 1)
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
	while ((*line)[i] && (*line)[i] != quote_type)
		i++;
	node->token = ft_strndup(*line, i - 1);
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
//TODO: DEBEMOS TENER EN CUENTA:
// || = Command Chaining? ZONA GRIS, NO SE INDICA EN NINGUN LADO
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
			check_pipes_and_redirs(token_list);
		}
	}
	check_join_quotes_because_special_chars(token_list);
	split_dollar(token_list, shell);
	join_nodes_because_quotes(&token_list);
	shell->cmds = create_new_cmds_node();
	group_by_pipes_and_redirs(shell, &token_list);
	return (token_list);
}
