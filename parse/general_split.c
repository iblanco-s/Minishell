/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inigo <inigo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 13:06:00 by inigo             #+#    #+#             */
/*   Updated: 2024/03/29 11:22:36 by inigo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_lstsize(t_env *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		lst = lst -> next;
		i++;
	}
	return (i);
}

char	**list_to_array(t_env *token_list)
{
	char	**tokens;
	t_env	*tmp;
	int		i;

	i = 0;
	tokens = malloc(sizeof(char *) * (ft_lstsize(token_list) + 1));
	while (token_list)
	{
		tmp = token_list;
		tokens[i] = token_list->name;
		token_list = token_list->next;
		free(tmp);
		i++;
	}
	tokens[i] = NULL;
	return (tokens);
}

t_env	*get_next_word(char **line)
{
	int		i;
	t_env	*node;

	node = malloc(sizeof(t_env));
	i = 0;
	while ((*line)[i] && (*line)[i] != ' ' && (*line)[i] != '\"' && (*line)[i] != '\'')
		i++;
	node->name = ft_strndup(*line, i - 1);
	node->single_quote = 0;
	node->next = NULL;
	*line += i;
	return (node);
}

t_env	*get_next_quote(char **line, int single_quote, char quote_type)
{
	int		i;
	t_env	*node;

	node = malloc(sizeof(t_env));
	i = 0;
	*line += 1;
	while ((*line)[i] && (*line)[i] != quote_type)
		i++;
	node->name = ft_strndup(*line, i - 1);
	node->next = NULL;
	node->single_quote = single_quote;
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
t_env	*general_split(char *line, t_cmds *cmds)
{
	t_env	*token_list;

	token_list = NULL;
	while (*line)
	{
		while (*line == ' ')
			line++;
		if (*line == '\"')
			ft_lstadd_back(&token_list, get_next_quote(&line, 0, '\"'));
		else if (*line == '\'')
			ft_lstadd_back(&token_list, get_next_quote(&line, 1, '\''));
		else if (*line)
		{
			ft_lstadd_back(&token_list, get_next_word(&line));
			check_pipes_and_redirs(token_list);
		}
	}
	// from echo hola$USER -> echo holaINIGO
	split_dollar(token_list, cmds);
	// from "echo holaINIGO | cat -e" -> nodo 1: "echo holaINIGO", nodo 2: "cat -e"
	group_by_pipes(&token_list);

	// Aqui printeo la lista, libero memoria y termino la ejecucion
	// para debuggear que se esta parseando bien, luego se eliminara
	t_env tmp = *token_list;
	while (tmp.next)
	{
		printf("Lista final: %s\n", tmp.name);
		tmp = *tmp.next;
	}
	printf("Lista final: %s\n", tmp.name);
	//free all env and  cmd
	t_env *tmp2;
	while (token_list)
	{
		tmp2 = token_list;
		token_list = token_list->next;
		free(tmp2->name);
		free(tmp2);
	}
	free_general(cmds);
	exit(0);
	
	return (token_list);
}
