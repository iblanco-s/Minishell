/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iblanco- <iblanco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 16:50:44 by iblanco-          #+#    #+#             */
/*   Updated: 2023/12/12 18:59:19 by iblanco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//TIene que haber almenos un char alfabetico?
int	check_alpha(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		if (ft_isalpha(str[i]))
			return (1);
		i++;
	}
	return (0);
}
//TODO sobreescibira si ya existe y =83843 no funciona
int ft_export(t_cmds *cmds)
{
    t_env *node;
	char *aux;
    int equal_sign;
	
	equal_sign = 0;
	while (cmds->opts[0][equal_sign] != '=' && cmds->opts[0][equal_sign])
		equal_sign++;
    if (equal_sign != 0 && cmds->opts[0][equal_sign])
    {
		aux = ft_strndup(cmds->opts[0], equal_sign - 1);
		if (check_alpha(aux) == 0)
		{
			printf("minishell: export: `%s': not a valid identifier\n", cmds->opts[0]);
			return (0);
		}
        node = (t_env *)malloc(sizeof(t_env));
        node->name = aux;
        node->value = ft_strdup(&cmds->opts[0][equal_sign] + 1);
		node->next = NULL;
		ft_lstadd_back(&cmds->env, node);
		return (1);
	}
	return (0);
}
