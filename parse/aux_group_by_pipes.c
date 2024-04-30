/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_group_by_pipes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-m <aecm.davidgomez@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 18:22:36 by inigo             #+#    #+#             */
/*   Updated: 2024/04/30 17:20:12 by dgomez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	free_list_parse(t_parse *list)
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
	new_node->infile_fd = NULL;
	new_node->outfile_fd = NULL;
	new_node->eof = NULL;
	new_node->write_mode = 0;
	new_node->next = NULL;
	return (new_node);
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

// void	debugg_print_cmds(t_cmds *current_cmd)
// {
// 	while (current_cmd)
// 	{
// 		printf("Command: ");
// 		if (!current_cmd->opts)
// 			return ;
// 		for (int i = 0; current_cmd->opts[i]; i++)
// 			printf("\n  %d: %s ", i, current_cmd->opts[i]);
// 		printf("\n");
// 		printf("Infile: ");
// 		if (current_cmd->infile)
// 		{
// 			for (int i = 0; current_cmd->infile[i]; i++)
// 				printf("%s ", current_cmd->infile[i]);
// 		}
// 		else
// 		{
// 			printf("null");
// 		}
// 		printf("\n");
// 		printf("Outfile: ");
// 		if (current_cmd->outfile)
// 		{
// 			for (int i = 0; current_cmd->outfile[i]; i++)
// 				printf("%s ", current_cmd->outfile[i]);
// 		}
// 		else
// 		{
// 			printf("null\n");
// 		}
// 		printf("\n");
// 		printf("Infile_fd: ");
// 		if (current_cmd->infile_fd)
// 		{
// 			int i = 0;
// 			while (current_cmd->infile_fd[i] != -1)
// 			{
// 				printf("%d ", current_cmd->infile_fd[i]);
// 				i++;
// 			}
// 		}
// 		else
// 		{
// 			printf("null");
// 		}
// 		printf("\n");
// 		printf("Outfile_fd: ");
// 		if (current_cmd->outfile_fd)
// 		{
// 			int i = 0;
// 			while (current_cmd->outfile_fd[i] != -1)
// 			{
// 				printf("%d ", current_cmd->outfile_fd[i]);
// 				i++;
// 			}
// 		}
// 		else
// 		{
// 			printf("null");
// 		}
// 		printf("\n");
// 		printf("Write_mode: %d\n", current_cmd->write_mode);
// 		printf("\n");
// 		current_cmd = current_cmd->next;
// 	}
// }
