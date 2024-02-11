/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_special_chars.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inigo <inigo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 13:07:09 by inigo             #+#    #+#             */
/*   Updated: 2024/02/11 17:59:53 by inigo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	divide_and_get_char(t_env *token_list, int i)
{
	t_env	*node_after_char;
	t_env	*node_char;

	node_after_char = malloc(sizeof(t_env));
	node_after_char->name = ft_strdup(&token_list->name[i + 1]);
	node_char = malloc(sizeof(t_env));
	node_char->name = malloc(sizeof(char) * 2);
	node_char->name[0] = token_list->name[i];
	node_char->name[1] = '\0';
	node_char->next = node_after_char;
	token_list->name[i] = '\0';
	node_after_char->next = token_list->next;
	token_list->next = node_char;
}

void	check_pipes_and_redirs(t_env *token_list)
{
	int	i;

	i = 0;
	token_list = ft_lstlast(token_list);
	while (token_list->name[i])
	{
		if (token_list->name[i] == '|' || token_list->name[i] == '<'
			|| token_list->name[i] == '>')
		{
			if (i > 0 || token_list->name[i + 1]) {
				divide_and_get_char(token_list, i);
				if (token_list->next->next)
					token_list = token_list->next;
			}
			break ; //NOSE SI EL BREAK VA DENTRO
		}
		i++;
	}
}
// Combines the og token + expanded value
// ex: test$HOME -> test /home/user -> test/home/user
void	combine(t_env *node, char *value_to_add)
{
	char	*tmp;

	if (node->name == NULL)
		node->name = ft_strdup(value_to_add);
	else
	{
		tmp = node->name;
		node->name = ft_strjoin(node->name, value_to_add);
		free(tmp);
	}
}
//TEST LINE= $PWD"$PWD"'$PWD'aaa$PWD"aaa$PWD"'aaa$PWD'$PWDaaa"$PWDaaa"'$PWDaaa'bbb$PWDbbb$PWD"bbb$PWDbbb$PWD"'bbb$PWDbbb$PWD'
//COEMNTAR FUNCIONES LUEGO  NO ME ACUERDO
void	divide_dollars(t_env *actual_node, t_cmds *cmds, int i)
{
	char	*stringToExpand;
	char	**splitted_dollars;
	//Y si hay $HOME$HOME??
	//Si no existe te lo comes ex: echo $HOME$NOEXISTW$HOME -> /home/user/home/user
	//Hacer split por $ y luego expandir, irar si expandir que envie NULL y entoces si es null pasas al siguiente
	splitted_dollars = ft_split(actual_node->name, '$');
	if (i > 0)
	{
		actual_node->name[i] = '\0';///esto da leaks no?
		i = 1;
	}
	else
	{
		free(actual_node->name);
		actual_node->name = NULL;
	}
	while (splitted_dollars[i])
	{
		stringToExpand = get_env_value(cmds, splitted_dollars[i]);
		if (stringToExpand)
			combine(actual_node, stringToExpand);
		free(splitted_dollars[i]);
		i++;
	}
	free(splitted_dollars);
	// stringToExpand = ft_strdup(&actual_node->name[i + 1]);
	// combine(actual_node, get_env_value(cmds, stringToExpand), i);
	// free(stringToExpand);
}

//HAY MOVIDA; tengp que controlar $HOME$HOME =  /home/user/home/user
//Y bbb$HOMEbbb peta porque no lo expande, es null y petardea
void	split_dollar(t_env *token_list, t_cmds *cmds)
{
	int		i;
	t_env	*head;

	i = 0;
	head = token_list;
	while (token_list && token_list->name)
	{
		if (token_list->single_quote != 1)
		{
			while (token_list->name[i])
			{
				if (token_list->name[i] == '$')
				{
					divide_dollars(token_list, cmds, i);
					break;
				}
				i++;
			}
		}
		token_list = token_list->next;
		i = 0;
	}
	token_list = head;
}
