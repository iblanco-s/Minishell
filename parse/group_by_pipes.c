/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   group_by_pipes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inigo <inigo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 10:31:59 by inigo             #+#    #+#             */
/*   Updated: 2024/04/16 23:37:11 by inigo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"


void	free_list(t_parse *list)
{
	t_parse	*tmp;

	while (list)
	{
		tmp = list;
		list = list->next;
		free(tmp->token);
		free(tmp);
	}
}

t_cmds	*create_new_cmds_node(void) 
{
	t_cmds	*new_node;
	
	new_node = malloc(sizeof(t_cmds));
	new_node->opts = NULL;
	new_node->aux_list_parse = NULL;
	new_node->infile = NULL;
	new_node->outfile = NULL;
	new_node->infile_fd = -1;
	new_node->outfile_fd = -1;
	new_node->eof = NULL;
	new_node->write_mode = 0;
	new_node->next = NULL;
	return new_node;
}

void add_option_to_cmds(t_cmds *cmd, char *option)
{
	t_env *aux_list_parse;

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

void set_input_redirection(t_cmds *cmd, int fd_type)
{
	t_env	*aux_list_parse;
	t_env	*prev;
	
	prev = NULL;
	cmd->infile_fd = fd_type;
	if (cmd->aux_list_parse)
	{
		aux_list_parse = cmd->aux_list_parse;
		while (aux_list_parse->next)
		{
			prev = aux_list_parse;
			aux_list_parse = aux_list_parse->next;
		}
		cmd->infile = ft_strdup(aux_list_parse->name);
		free(aux_list_parse->name);
		aux_list_parse->name = NULL;
		// free(aux_list_parse);
		if (prev)
			prev->next = NULL;
	}
}

void set_output_redirection(t_cmds *cmd, t_parse **current, int fd_type)
{
	cmd->outfile_fd = fd_type;
	if ((*current)->next)
	{
		cmd->outfile = strdup((*current)->next->token);
		*current = (*current)->next->next;
	}
}

int	check_reddirs(t_parse **current, t_cmds *current_cmd)
{
	int enter;

	enter = 1;
	if (strcmp((*current)->token, "<") == 0)
		set_input_redirection(current_cmd, 1);
	else if (strcmp((*current)->token, "<<") == 0)
		set_input_redirection(current_cmd, 2);
	else if (strcmp((*current)->token, ">>") == 0)
		set_output_redirection(current_cmd, current, 1);
	else if (strcmp((*current)->token, ">") == 0)
		set_output_redirection(current_cmd, current, 2);
	else
		enter = 0;
	return enter;
}

int	ft_lstsize_tenv(t_env *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		if (lst->name == NULL)
		{
			lst = lst -> next;
			continue ;
		}
		lst = lst -> next;
		i++;
	}
	return (i);
}

char	**list_to_array(t_env *token_list)
{
	char	**tokens;
	t_env	*tmp;
	int		i;

	i = 0;
	tokens = malloc(sizeof(char *) * (ft_lstsize_tenv(token_list) + 1));
	while (token_list)
	{
		tmp = token_list;
		if (tmp->name == NULL)
		{
			token_list = token_list->next;
			free(tmp);
			continue ;
		}
		tokens[i] = ft_strdup(token_list->name);
		token_list = token_list->next;
		free(tmp->name);
		free(tmp);
		i++;
	}
	tokens[i] = NULL;
	return (tokens);
}

// Modified group_by_pipes function
void group_by_pipes_and_redirs(t_shell *shell, t_parse **token_list)
{
	t_parse *current;
	t_cmds *cmds_head;
	t_cmds *current_cmd;
	int		enter;
	
	current = *token_list;
	cmds_head = create_new_cmds_node();
	current_cmd = cmds_head;
	shell->cmds = *cmds_head;
	while (current)
	{
		if (current->token[0] == '|' && current->token[1] == '\0')
		{
			current_cmd->opts = list_to_array(current_cmd->aux_list_parse);
			current_cmd->next = create_new_cmds_node();
			current_cmd = current_cmd->next;
		} 
		else
		{
			if (current->quote == 0)
				enter = check_reddirs(&current, current_cmd);
			if (current && enter == 0)
				add_option_to_cmds(current_cmd, current->token);
		}
		if (current)
			current = current->next;
	}
	if (current_cmd->aux_list_parse)
		current_cmd->opts = list_to_array(current_cmd->aux_list_parse);
	free_list(*token_list); // Free the original token list
	//debugg print
	current_cmd = cmds_head;
	while (current_cmd)
	{
		printf("Command: ");
		for (int i = 0; current_cmd->opts[i]; i++)
			printf("\n  %d: %s ", i, current_cmd->opts[i]);
		printf("\n");
		printf("Infile: %s\n", current_cmd->infile);
		printf("Outfile: %s\n", current_cmd->outfile);
		printf("Infile_fd: %d\n", current_cmd->infile_fd);
		printf("Outfile_fd: %d\n", current_cmd->outfile_fd);
		printf("Write_mode: %d\n", current_cmd->write_mode);
		current_cmd = current_cmd->next;
	}
}
