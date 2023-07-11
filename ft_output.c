/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_output.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandom <aandom@student.abudhabi42.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 20:13:40 by aandom            #+#    #+#             */
/*   Updated: 2023/07/08 20:13:40 by aandom           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void	ft_append(t_data *data, t_cmd **cmds, t_lexer **token)
{
	t_cmd       *lastcmd;
    t_lexer     *tmp;
    t_iofiles   *iofds;
    int         fd;

    tmp = *token;
    lastcmd = get_last_cmd(*cmds);
    initialize_iofds(lastcmd);
    iofds = lastcmd->iofiles;
    printf("infile- %s\n", iofds->infile);
    printf("type0 == %d\n", tmp->next->type);
    if(!remove_prev_iofds(iofds, 2))
    {
        printf("returned 0\n");
        return ;
    }
    printf("type == %d\n", tmp->next->type);
    if (tmp->next->type == END || tmp->next->str[0] == '\0')
    {
        printf("syntax error near unexpected token\n");
        exit(0);
        return ;
    }
    iofds->outfile = ft_strdup(tmp->next->str);
    fd = open(iofds->outfile, O_WRONLY | O_APPEND | O_CREAT, 0664);
    if (fd == -1)
    {
        printf("error while opening a file\n");
        exit(1);
        return ;
    }
    iofds->fdout = fd;
    if (tmp->next->next)
    {
        tmp = tmp->next->next;
    }
    else
        tmp = tmp->next;
    *token = tmp;
}
