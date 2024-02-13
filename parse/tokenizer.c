/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inigo <inigo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 17:13:39 by inigo             #+#    #+#             */
/*   Updated: 2024/02/12 19:49:20 by inigo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// char	**expander(char **tokenized_line, t_cmds *cmds)
// {
// 	int		i;
// 	char	*value;

// 	i = 0;
// 	while (tokenized_line[i])
// 	{
// 		if (tokenized_line[i][0] == '$')
// 		{
// 			value = get_env_value(cmds, &tokenized_line[i][1]);
// 			free(tokenized_line[i]);
// 			if (value)
// 				tokenized_line[i] = ft_strdup(value);
// 			else
// 				tokenized_line[i] = ft_strdup("");
// 		}
// 		i++;
// 	}
// 	return (tokenized_line);
// }
t_env *expander(t_env *env_list, t_cmds *cmds)
{
	t_env *current = env_list;
	char *value;

	while (current)
	{
		if (current->name[0] == '$' && current->single_quote == 0)
		{
			value = get_env_value(cmds, &current->name[1]);
			free(current->name);
			if (value)
				current->name = ft_strdup(value);
			else
				current->name = ft_strdup("");
		}
		current = current->next;
	}
	return env_list;
}
void	handle_input(char *line, t_cmds *cmds)
{
	char	**tokenized_line;

	tokenized_line = list_to_array(general_split(line, cmds));
	printf("tokenized_line: %s\n", tokenized_line[0]);
}
