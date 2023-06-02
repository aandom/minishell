/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandom <aandom@student.abudhabi42.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 19:41:55 by aandom            #+#    #+#             */
/*   Updated: 2023/06/02 22:07:22 by aandom           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int check_token(char *str, int i, int type);
{
    if (str[i] == '|')
        return (PIPE);
    if ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
        return (STAB);
    if (str[i] == '>' && str[i + 1] == '>')
        return (GREAT_GREAT);
    if (str[i] == '<' && str[i + 1] == '<')
        return (LESS_LESS);
    if (str[i] == '>')
        return (GREAT);
    if (str[i] == '<')
        return (LESS);
    if (str[i] == '\0')
        return (END);
    else 
        return (0);
    
}

int check_quote(char *str, int i, int quote)
{
    if (str[i] == '\'' && quote == NONE)
        quote = SINGLE;
    else if (str[i] == '\"' && quote == NONE)
        quote = DOUBLE;
    else
        quote = NONE;
    return(quote);
}

void    ft_parser(t_data *data)
{
    size_t i;
    size_t start;
    size_t end;
    int    t_type;

    end = ft_strlen(data->input);
    i = 0;
    t_type = 0;
    while (data->input[i])
    {
        t_type = check_token(data->input, i, t_type);
        
    }
}