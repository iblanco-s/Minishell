/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inigo <inigo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 17:13:39 by inigo             #+#    #+#             */
/*   Updated: 2024/01/13 19:11:48 by inigo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	**expander(char **tokenized_line, t_cmds *cmds)
{
	int		i;
	char	*value;

	i = 0;
	while (tokenized_line[i])
	{
		if (tokenized_line[i][0] == '$')
		{
			value = get_env_value(cmds, &tokenized_line[i][1]);
			free(tokenized_line[i]);
			if (value)
				tokenized_line[i] = ft_strdup(value);
			else
				tokenized_line[i] = ft_strdup("");
		}
		i++;
	}
	return (tokenized_line);
}

void	handle_input(char *line, t_cmds *cmds)
{
	char	**tokenized_line;

	tokenized_line = expander(general_split(line), cmds);
}
