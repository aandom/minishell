/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iofds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandom <aandom@student.abudhabi42.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 12:10:07 by aandom            #+#    #+#             */
/*   Updated: 2023/07/06 12:10:07 by aandom           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    initialize_iofds(t_cmd  *cmd)
{
    if (cmd->iofiles)
        return ;
    cmd->iofiles = malloc(sizeof(t_iofiles));
    if (!cmd->iofiles)
        return ;
    cmd->iofiles->infile = NULL;
    cmd->iofiles->outfile = NULL;
    cmd->iofiles->fdin = -1;
    cmd->iofiles->fdout = -1;
    cmd->iofiles->here_delimter = NULL;
}

int remove_prev_iofds(t_iofiles *iofds, int code)
{
    if (iofds->infile && code == 1)
    {
        if ((iofds->outfile && iofds->fdout == -1) || iofds->fdin == -1)
            return (0);
        if (iofds->here_delimter != NULL)
        {
            free(iofds->here_delimter);
            iofds->here_delimter == NULL;
            unlink(iofds->infile);
        }
        free(iofds->infile);
        close(iofds->fdin); 
        return (1);
    }
    else if (iofds->infile && code == 2)
    {
        if ((iofds->outfile && iofds->fdout == -1) || iofds->fdin == -1)
            return (0);
        
    }
    else
        return (1);
}