/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inigo <inigo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 20:57:44 by inigo             #+#    #+#             */
/*   Updated: 2024/04/03 18:17:53 by inigo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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

char	*check_single_quote(char *string_to_check)
{
	char	*return_str;
	int		i;

	i = 0;
	return_str = NULL;
	while (string_to_check[i])
	{
		if (string_to_check[i] == '\'')
		{
			return_str = ft_strdup(&string_to_check[i]);
			string_to_check[i] = '\0';
			break ;
		}
		i++;
	}
	return (return_str);
}

void	expand_and_combine(t_env *actual_node,
	t_cmds *cmds, char **split_by_dollar, int i)
{
	char	*splitted_single_quote;
	char	*string_to_expand;

	while (split_by_dollar[i])
	{
		splitted_single_quote = check_single_quote(split_by_dollar[i]);
		string_to_expand = get_env_value(cmds, split_by_dollar[i]);
		if (string_to_expand)
			combine(actual_node, string_to_expand);
		free(string_to_expand);
		free(split_by_dollar[i]);
		if (splitted_single_quote)
		{
			combine(actual_node, splitted_single_quote);
			free(splitted_single_quote);
			splitted_single_quote = NULL;
		}
		i++;
	}
}

// TEST LINE= $PWD"$PWD"'$PWD'aaa$PWD"aaa$PWD"'aaa$PWD'$PWDaaa"$PWDaaa"
// '$PWDaaa'bbb$PWDbbb$PWD"bbb$PWDbbb$PWD"'bbb$PWDbbb$PWD' 
// a$USER a'a$USER'bb a$USERa$USER a|b a| |b a$HOMEa
// COEMNTAR FUNCIONES LUEGO  NO ME ACUERDO 
// a$USER a'a$USER'bb a$USERa$USER a|b a| |b a$HOMEa
void	divide_dollars(t_env *actual_node, t_cmds *cmds, int i)
{
	char	**split_by_dollar;

	split_by_dollar = ft_split(actual_node->name, '$');
	if (i > 0)
	{
		actual_node->name[i] = '\0';
		i = 1;
		free(split_by_dollar[0]);
	}
	else
	{
		free(actual_node->name);
		actual_node->name = NULL;
	}
	expand_and_combine(actual_node, cmds, split_by_dollar, i);
	free(split_by_dollar);
}

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
					break ;
				}
				i++;
			}
		}
		token_list = token_list->next;
		i = 0;
	}
	token_list = head;
}
