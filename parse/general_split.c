/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inigo <inigo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 13:06:00 by inigo             #+#    #+#             */
/*   Updated: 2024/02/11 18:23:41 by inigo            ###   ########.fr       */
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

//ERROR= "'$HOME'"y'"$HOME"'
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
	split_dollar(token_list, cmds);
	t_env tmp = *token_list;
	while (tmp.next)
	{
		printf("Lista final: %s\n", tmp.name);
		tmp = *tmp.next;
	}
	printf("Lista final: %s\n", tmp.name);
	return (token_list);
}
