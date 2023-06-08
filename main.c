/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandom <aandom@student.abudhabi42.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 14:11:56 by aandom            #+#    #+#             */
/*   Updated: 2023/06/08 17:03:48 by aandom           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    ft_minishell()
{
    t_data  *data;
    
    data = malloc(sizeof(t_data));
    while (1)
    {
        data->input = readline(PROMPT);
        // ft_lexer(data);
        ft_parser(data);
        int i = 0;
        t_lexer *tmp;
        tmp = data->lexed;
        while (tmp)
        {
            printf("%s ", tmp->str);
            tmp = tmp->next;
        }
        printf("\n");
        free(data->input);
    }
}

int main(int ac, char **av, char **env)
{
    (void) av;
    (void) env;
    if (ac != 1)
        return (0);
    ft_minishell();
}