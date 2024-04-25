/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   group_by_pipes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsalaber <jsalaber@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 10:31:59 by inigo             #+#    #+#             */
/*   Updated: 2024/04/24 11:45:19 by jsalaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	add_option_to_cmds(t_cmds *cmd, char *option)
{
	t_env	*aux_list_parse;

	if (cmd->aux_list_parse == NULL)
	{
		cmd->aux_list_parse = malloc(sizeof(t_env));
		cmd->aux_list_parse->name = ft_strdup(option);
		cmd->aux_list_parse->next = NULL;
	}
	else
	{
		if (cmd->aux_list_parse->next == NULL)
			aux_list_parse = cmd->aux_list_parse;
		else
			aux_list_parse = ft_lstlast(cmd->aux_list_parse);
		aux_list_parse->next = malloc(sizeof(t_env));
		aux_list_parse->next->name = ft_strdup(option);
		aux_list_parse->next->next = NULL;
	}
}

int	check_reddirs(t_parse **current, t_cmds *current_cmd)
{
	int	enter;

	enter = -1;
	if (ft_strcmp((*current)->token, "<") == 0)
		set_input_redirection(current_cmd, current, 1);
	else if (ft_strcmp((*current)->token, "<<") == 0)
		set_input_redirection(current_cmd, current, 2);
	else if (ft_strcmp((*current)->token, ">>") == 0)
		set_output_redirection(current_cmd, current, 2);
	else if (ft_strcmp((*current)->token, ">") == 0)
		set_output_redirection(current_cmd, current, 1);
	else
		enter = 0;
	return (enter);
}

// c -> current
// c_cmd -> current command
void	group_by_pipes_and_redirs(t_shell *shell, t_parse **token_list)
{
	t_parse	*c;
	t_cmds	*c_cmd;

	c = *token_list;
	c_cmd = shell->cmds;
	while (c)
	{
		if (c->token == NULL)
		{
			c = c->next;
			continue ;
		}
		if (c->token[0] == '|' && c->token[1] == '\0')
		{
			c_cmd->opts = list_to_array(c_cmd->aux_list_parse);
			c_cmd = (c_cmd->next = create_new_cmds_node());
		}
		else
		{
			if (!(c->quote == 0))
				add_option_to_cmds(c_cmd, c->token);
			else if (c->quote == 0 && !check_reddirs(&c, c_cmd))
				add_option_to_cmds(c_cmd, c->token);
		}
		if (c)
			c = c->next;
	}
	if (c_cmd->aux_list_parse)
		c_cmd->opts = list_to_array(c_cmd->aux_list_parse);
	free_list_parse(*token_list);
	// c_cmd = shell->cmds;
	// debugg_print_cmds(c_cmd);
}
