/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-m <aecm.davidgomez@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 16:58:52 by dgomez-m          #+#    #+#             */
/*   Updated: 2024/04/30 16:59:28 by dgomez-m         ###   ########.fr       */
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
