/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_out_files.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junesalaberria <junesalaberria@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 10:09:11 by junesalaber       #+#    #+#             */
/*   Updated: 2024/04/11 10:42:28 by junesalaber      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//meto el parametro node para indicar que aqui deberia entrar el nodo completo
// antes de hacer la separacion

// retorna 0 cuando no hay redireccion
// retorna 1 cuando es redireccion
// retorna 2 cuando es heredoc
int	in_redir_type(char *node)
{
	while (ft_isspace(*node))
		node++;
	if (!*node)
		return (0);
	while (*node)
	{
		if (*node == '<')
		{
			if (*node + 1 == '<')
				return (2);
			return (1);
		}
	}
	return (0);
}

// retorna 0 cuando no hay redireccion
// retorna 1 cuando es redireccion
// retorna 2 cuando es apend
int	out_redir_type(char *node)
{
	while (*node && *node != '>')
		node++;
	if (!*node)
		return (0);
	while (*node)
	{
		if (*node == '<')
		{
			if (*node + 1 == '<')
				return (2);
			return (1);
		}
	}
	return (0);
}

//coge el nombre del infile
char	infile_name(char *node)
{
	int	len;

	while (ft_isspace(*node))
		node++;
	if (!*node)
		return (NULL);
	if (*node == '<')
	{
		node++;
		if (*node =='<')
			node++;
	}
	while (ft_isspace(*node))
		node++;
	len = 0;
	while (*node =! ' ')
		len++;
	return (ft_substr(node, 0, len));
}

//coge el nombre del outfile 
char	outfile_name(char *node)
{
	int	len;
	
	while (*node && *node != '>')
		node++;
	if (*node == '>')
	{
		node++;
		if (*node == '>')
			node++;
	}
	while (ft_isspace(*node))
		node++;
	len = 0;
	while (*node !=' ')
		len++;
	return (ft_substr(node, 0 , len));
}