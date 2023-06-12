/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandom <aandom@student.abudhabi42.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 19:20:51 by aandom            #+#    #+#             */
/*   Updated: 2023/06/10 17:14:20 by aandom           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void    ft_lexer(t_data *data, char *line)
// {
//     int i;
    
//     i = -1;
//     while (line[++i])
//     {
        
//     }
// }

int inside_quote(char *str)
{
    if (check_quote(str, 0, NOQUOTE) == SINGLE || check_quote(str, 0, NOQUOTE) == DOUBLE)
        return (1);
    return(0);
}

void    trim_quote(t_lexer **lexed)
{
    t_lexer *tmp;
    char    *str;

    tmp = *lexed;
    str = ft_strtrim(tmp->str, '\"');
    free(tmp->str);
    tmp->str = str;
}

void    remove_quotes(t_lexer **lexed)
{
    t_lexer *tmp;

    tmp = *lexed;
    while(tmp)
    {
        if (inside_quote(tmp->str) && tmp->prev->type != LESS_LESS)
            trim_quote(&tmp);
        tmp = tmp->next;
    }
}