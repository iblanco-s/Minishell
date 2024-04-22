/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   group_by_pipes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsalaber <jsalaber@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 10:31:59 by inigo             #+#    #+#             */
/*   Updated: 2024/04/22 11:21:00 by jsalaber         ###   ########.fr       */
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

// Modified group_by_pipes function
void	group_by_pipes_and_redirs(t_shell *shell, t_parse **token_list)
{
	t_parse	*current;
	t_cmds	*current_cmd;

	current = *token_list;
	current_cmd = shell->cmds;
	while (current)
	{
		if (current->token[0] == '|' && current->token[1] == '\0')
		{
			current_cmd->opts = list_to_array(current_cmd->aux_list_parse);
			current_cmd = (current_cmd->next = create_new_cmds_node());
			// current_cmd->next = create_new_cmds_node();
			// current_cmd = current_cmd->next;
		}
		else
		{
			if (!(current->quote == 0))
				add_option_to_cmds(current_cmd, current->token);
			else if (current->quote == 0 && !check_reddirs(&current, current_cmd))
				add_option_to_cmds(current_cmd, current->token);
		}
		if (current)
			current = current->next;
	}
	if (current_cmd->aux_list_parse)
		current_cmd->opts = list_to_array(current_cmd->aux_list_parse);
	free_list_parse(*token_list);
	// current_cmd = shell->cmds;
	// debugg_print_cmds(current_cmd);
}



// // Modified group_by_pipes function
// void	group_by_pipes_and_redirs(t_shell *shell, t_parse **token_list)
// {
// 	t_parse	*current;
// 	t_cmds	*cmds_head;
// 	t_cmds	*current_cmd;
// 	int		enter;

// 	current = *token_list;
// 	cmds_head = create_new_cmds_node();
// 	current_cmd = cmds_head;
// 	shell->cmds = *cmds_head;
// 	while (current)
// 	{
// 		if (current->token[0] == '|' && current->token[1] == '\0')
// 		{
// 			current_cmd->opts = list_to_array(current_cmd->aux_list_parse);
// 			current_cmd->next = create_new_cmds_node();
// 			current_cmd = current_cmd->next;
// 		}
// 		else
// 		{
// 			if (current->quote == 0)
// 				enter = check_reddirs(&current, current_cmd);
// 			if (current && enter == 0)
// 				add_option_to_cmds(current_cmd, current->token);
// 		}
// 		if (current)
// 			current = current->next;
// 	}
// 	if (current_cmd->aux_list_parse)
// 		current_cmd->opts = list_to_array(current_cmd->aux_list_parse);
// 	free_list_parse(*token_list);
// 	current_cmd = cmds_head;
// 	debugg_print_cmds(current_cmd);
// }


// minishell$ "yo'muy'bien"como"que"<pacasa>unapollla"losacofacil"
// inigo@MacBook-Pro-de-Mikel Minishell % echo "yo'muy'bien"como"que"<pacasa>unapollla"losacofacil"
// inigo@MacBook-Pro-de-Mikel Minishell % ./minishell 
// minishell$ "yo'muy'bien"como"que"<pacasa
// entroo22entrooentroo22Command: 
//   0: yo'muy'biencomoque< 
//   1: pacasa 
// Infile: null
// Outfile: null

// Infile_fd: null
// Outfile_fd: null
// Write_mode: 0

// minishell$ 
// inigo@MacBook-Pro-de-Mikel Minishell % echo "yo'muy'bien"como"que"<pacasa
// zsh: no such file or directory: pacasa
// inigo@MacBook-Pro-de-Mikel Minishell % echo "yo'muy'bien"como<no"que"pacasa
// zsh: no such file or directory: noquepacasa
// inigo@MacBook-Pro-de-Mikel Minishell % ./minishell 
// minishell$ echo "yo'muy'bien"como<no"que"pacasa
// entrooentroo22entroo22entrooentroo22entroo22Command: 
//   0: echo 
//   1: yo'muy'biencomo< 
//   2: no 
//   3: quepacasa 
// Infile: null
// Outfile: null

// Infile_fd: null
// Outfile_fd: null
// Write_mode: 0

// minishell$ 