/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghoyuelo <ghoyuelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 14:35:58 by ghoyuelo          #+#    #+#             */
/*   Updated: 2023/11/29 14:35:58 by ghoyuelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"
void    *get_env(char **env)
{
    int i;
    char **tmp;

    i = 0;
    while(env[i])
        i++;
    tmp = malloc(i, sizeof(char *));
    if (!tmp)
        print_error("Malloc error.");
        
    
}

void   init_term(t_data *data,char **env)
{
    t_data    *data;

    data = malloc(sizeof(t_data));
    data->mini_env = get_env(env);
    if (!get_env(env))
        print_erorr("Enviroment error.");
}


int main( int argc, char **argv, char **env)
{
    t_data  *data;
    
    (void)argv;
    if (argc != 1)
        print_error("Error! Invalid arguments.");
    init_term(data,env);

}
