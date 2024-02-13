/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_special_chars.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inigo <inigo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 13:07:09 by inigo             #+#    #+#             */
/*   Updated: 2024/02/13 11:57:50 by inigo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void divide_and_get_char(t_env *token_list, int i)
{
	t_env *node_after_char;
	t_env *node_with_char;

	node_after_char = NULL;
	node_with_char = NULL;
	if (token_list->name[i + 1])
	{
		node_after_char = malloc(sizeof(t_env));
		node_after_char->name = ft_strdup(&token_list->name[i + 1]); // esta bien cortado por ahi?
		token_list->name[i + 1] = '\0'; // esto da leaks no?
		node_after_char->next = token_list->next;
		token_list->next = node_after_char;
	}
	if (i > 0)
	{
		node_with_char = malloc(sizeof(t_env));
		node_with_char->name = ft_strdup(&token_list->name[i]);
		token_list->name[i] = '\0';
		if (node_after_char)
			node_with_char->next = node_after_char;
		else
			node_with_char->next = token_list->next;
		token_list->next = node_with_char;
	}
}

void check_pipes_and_redirs(t_env *token_list)
{
	int i;

	i = 0;
	token_list = ft_lstlast(token_list);
	while (token_list->name[i])
	{
		if (token_list->name[i] == '|' || token_list->name[i] == '<' || token_list->name[i] == '>')
		{
			if (i > 0 || token_list->name[i + 1])
			{
				divide_and_get_char(token_list, i);
				// if (token_list->next->next) //esto para q
				// 	token_list = token_list->next;
			}
			break; // NOSE SI EL BREAK VA DENTRO
		}
		i++;
	}
}
// Combines the og token + expanded value
// ex: test$HOME -> test /home/user -> test/home/user
void combine(t_env *node, char *value_to_add)
{
	char *tmp;

	if (node->name == NULL)
		node->name = ft_strdup(value_to_add);
	else
	{
		tmp = node->name;
		node->name = ft_strjoin(node->name, value_to_add);
		free(tmp);
	}
}

char *check_single_quote(char *string_to_check)
{
	char *return_str;
	int i;

	i = 0;
	return_str = NULL;
	while (string_to_check[i])
	{
		if (string_to_check[i] == '\'')
		{
			return_str = ft_strdup(&string_to_check[i]);
			string_to_check[i] = '\0';
			break;
		}
		i++;
	}
	return (return_str);
}

void expand_and_combine(t_env *actual_node, t_cmds *cmds, char **split_by_dollar, int i)
{
	char *splitted_single_quote;
	char *stringToExpand;

	while (split_by_dollar[i])
	{
		splitted_single_quote = check_single_quote(split_by_dollar[i]);
		stringToExpand = get_env_value(cmds, split_by_dollar[i]);
		if (stringToExpand)
			combine(actual_node, stringToExpand);
		free(split_by_dollar[i]);
		if (splitted_single_quote)
		{
			combine(actual_node, splitted_single_quote);
			free(splitted_single_quote);
			splitted_single_quote = NULL;
		}
		i++;
	}
	free(split_by_dollar);
}
// TEST LINE= $PWD"$PWD"'$PWD'aaa$PWD"aaa$PWD"'aaa$PWD'$PWDaaa"$PWDaaa"'$PWDaaa'bbb$PWDbbb$PWD"bbb$PWDbbb$PWD"'bbb$PWDbbb$PWD'
// COEMNTAR FUNCIONES LUEGO  NO ME ACUERDO
void divide_dollars(t_env *actual_node, t_cmds *cmds, int i)
{
	char **split_by_dollar;

	split_by_dollar = ft_split(actual_node->name, '$');
	if (i > 0)
	{
		actual_node->name[i] = '\0'; /// esto da leaks no?
		i = 1;
	}
	else
	{
		free(actual_node->name);
		actual_node->name = NULL;
	}
	expand_and_combine(actual_node, cmds, split_by_dollar, i);
}

void split_dollar(t_env *token_list, t_cmds *cmds)
{
	int i;
	t_env *head;

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
