/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsalaber <jsalaber@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 20:57:44 by inigo             #+#    #+#             */
/*   Updated: 2024/04/26 09:41:26 by jsalaber         ###   ########.fr       */
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

char	*expand_quote(char *string_to_expand)
{
	char	*expanded_value;
	char	*tmp;

	tmp = NULL;
	expanded_value = ft_itoa(g_exit_status);
	tmp = expanded_value;
	if (string_to_expand[1])
	{
		tmp = ft_strjoin(expanded_value, ft_strdup(&string_to_expand[1]));
		free(expanded_value);
	}
	return (tmp);
}

void	expand_and_combine(t_parse *actual_node,
	t_shell *shell, char **split_by_dollar, int i)
{
	char	*splitted_single_quote;
	char	*string_to_expand;

	while (split_by_dollar[i])
	{
		splitted_single_quote = check_single_quote(split_by_dollar[i]);
		if (split_by_dollar[i][0] == '?')
			string_to_expand = expand_quote(split_by_dollar[i]);
		else
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

// TEST LINE= $PWD"$PWD"'$PWD'aaa$PWD"aaa$PWD"'aaa$PWD'$PWDaaa"$PWDaaa"
// '$PWDaaa'bbb$PWDbbb$PWD"bbb$PWDbbb$PWD"'bbb$PWDbbb$PWD' 
// a$USER a'a$USER'bb a$USERa$USER a|b a| |b a$HOMEa
// COEMNTAR FUNCIONES LUEGO  NO ME ACUERDO 
// a$USER a'a$USER'bb a$USERa$USER a|b a| |b a$HOMEa
void	divide_dollars(t_parse *actual_node, t_shell *shell, int i)
{
	char	**split_by_dollar;

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

t_parse	*check_if_token_is_empty(t_parse *token_list)
{
	if (token_list->token == NULL)
		token_list = token_list->next;
	return (NULL);
}

void	split_dollar(t_parse *token_list, t_shell *shell)
{
	int		i;
	t_parse	*head;

	i = 0;
	head = token_list;
	while (token_list)
	{
		if (check_if_token_is_empty(token_list))
			continue ;
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
	delete_empty_nodes(&head);
}
