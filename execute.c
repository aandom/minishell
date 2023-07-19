/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandom <aandom@student.abudhabi42.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 23:30:16 by aandom            #+#    #+#             */
/*   Updated: 2023/07/17 23:30:16 by aandom           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int ft_check_iofiles(t_iofiles *iofds)
{
    if (!iofds || (!iofds->infile && !iofds->outfile))
        return (1);
    if ((iofds->infile && iofds->fdin == -1) || (iofds->outfile && iofds->fdout == -1))
        return (0);
    return (1);
}


int create_pipes(t_data *data)
{
    int     *tube;
    t_cmd   *cmds;

    cmds = data->cmds;
    while(cmds)
    {
        if (cmds->pipeout || (cmds->prev && cmds->prev->pipeout))
        {
            tube = malloc(sizeof(int) * 2);
            if (!tube || pipe(tube) != 0)
                return (0);
            cmds->tube = tube;
        }
        cmds = cmds->next;
    }
    return(1);
}

static  int check_prepare_exec(t_data *data)
{
    if (!data || !data->cmds)
        return(EXIT_SUCCESS);
    if (!data->cmds->cmd)
    {
        if (data->cmds->iofiles && !ft_check_iofiles(data->cmds->iofiles))
            return (EXIT_FAILURE);
        return (EXIT_SUCCESS);
    }
    
    if (!create_pipes(data))
        return(EXIT_FAILURE);
    return (127);

}


int execute(t_data *data)
{
    int res;

    res = check_prepare_exec(data);
    if (res != 127)
        return (res);
    
}