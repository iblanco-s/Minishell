/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inigo <inigo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 20:57:44 by inigo             #+#    #+#             */
/*   Updated: 2024/04/21 21:44:59 by inigo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// Combines the og token + expanded value
// ex: test$HOME -> test /home/user -> test/home/user
void	combine(t_parse *node, char *value_to_add)
{
	char	*tmp;

	if (node->token == NULL)
		node->token = ft_strdup(value_to_add);
	else
	{
		tmp = node->token;
		node->token = ft_strjoin(node->token, value_to_add);
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

void	expand_and_combine(t_parse *actual_node,
	t_shell *shell, char **split_by_dollar, int i)
{
	char	*splitted_single_quote;
	char	*string_to_expand;

	while (split_by_dollar[i])
	{
		splitted_single_quote = check_single_quote(split_by_dollar[i]);
		string_to_expand = get_env_value(shell, split_by_dollar[i]);
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

// GESTIONAR MULTIPLE $ CON $?
// int	check_question(t_parse *actual_node, int i)
// {
// 	char	*string_to_expand;
// 	char	*tmp;
// 	char	*tmp2;

// 	if (actual_node->token[i + 1] == '?')
// 	{
// 		string_to_expand = ft_itoa(g_exit_status);
// 		tmp = actual_node->token;
// 		if (actual_node->token[i + 2])
// 		{
// 			tmp2 = string_to_expand;
// 			string_to_expand = ft_strjoin(string_to_expand, ft_strdup(&actual_node->token[i + 2]));
// 			free(tmp2);
// 		}
// 		else
// 			actual_node->token = ft_strdup(string_to_expand);
// 		if (i > 0)
// 			actual_node->token[i] = '\0';
// 		else
// 			actual_node->token = NULL;
// 		combine(actual_node, string_to_expand);
// 		free(tmp);
// 		free(string_to_expand);
// 		return (1);
// 	}
// 	return (0);
// }

// TEST LINE= $PWD"$PWD"'$PWD'aaa$PWD"aaa$PWD"'aaa$PWD'$PWDaaa"$PWDaaa"
// '$PWDaaa'bbb$PWDbbb$PWD"bbb$PWDbbb$PWD"'bbb$PWDbbb$PWD' 
// a$USER a'a$USER'bb a$USERa$USER a|b a| |b a$HOMEa
// COEMNTAR FUNCIONES LUEGO  NO ME ACUERDO 
// a$USER a'a$USER'bb a$USERa$USER a|b a| |b a$HOMEa
void	divide_dollars(t_parse *actual_node, t_shell *shell, int i)
{
	char	**split_by_dollar;

	// if (check_question(actual_node, i))
	// 	return ;
	split_by_dollar = ft_split(actual_node->token, '$');
	if (i > 0)
	{
		actual_node->token[i] = '\0';
		i = 1;
		free(split_by_dollar[0]);
	}
	else
	{
		free(actual_node->token);
		actual_node->token = NULL;
	}
	expand_and_combine(actual_node, shell, split_by_dollar, i);
	free(split_by_dollar);
}

void	split_dollar(t_parse *token_list, t_shell *shell)
{
	int		i;
	t_parse	*head;

	i = 0;
	head = token_list;
	while (token_list && token_list->token)
	{
		if (token_list->quote != 1)
		{
			while (token_list->token[i])
			{
				if (token_list->token[i] == '$' && token_list->token[i + 1])
				{
					divide_dollars(token_list, shell, i);
					break ;
				}
				i++;
			}
		}
		token_list = token_list->next;
		i = 0;
	}
	token_list = head;
	delete_empty_nodes(&token_list);
}
