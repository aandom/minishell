/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iofds.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandom <aandom@student.abudhabi42.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 19:52:57 by aandom            #+#    #+#             */
/*   Updated: 2023/08/07 19:52:57 by aandom           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_iofiles(t_iofiles *iofds)
{
	if (!iofds || (!iofds->infile && !iofds->outfile))
		return (1);
	if ((iofds->infile && iofds->fdin == -1) || \
		(iofds->outfile && iofds->fdout == -1))
		return (0);
	return (1);
}

void	reset_stdio(t_iofiles *iofds)
{
	if (!iofds)
		return ;
	if (iofds->stdin_cp != -1)
	{
		if (dup2(iofds->stdin_cp, STDIN_FILENO) == -1)
			return ;
		close(iofds->stdin_cp);
		iofds->stdin_cp = -1;
	}
	if (iofds->stdout_cp != -1)
	{
		if (dup2(iofds->stdout_cp, STDOUT_FILENO) == -1)
			return ;
		close(iofds->stdout_cp);
		iofds->stdout_cp = -1;
	}
	return ;
}

void	close_iofds(t_cmd *cmds, int code)
{
	if (cmds->iofiles)
	{
		if (cmds->iofiles->fdin != -1)
			close(cmds->iofiles->fdin);
		if (cmds->iofiles->fdout != -1)
			close (cmds->iofiles->fdout);
		if (code == 1)
			reset_stdio(cmds->iofiles);
	}
	close_unused_pipes(cmds, NULL);
}

void	set_iofds(t_iofiles *iofds)
{
	if (!iofds)
		return ;
	iofds->stdin_cp = dup(STDIN_FILENO);
	if (iofds->stdin_cp == -1)
		return ;
	iofds->stdout_cp = dup(STDOUT_FILENO);
	if (iofds->stdout_cp == -1)
		return ;
	if (iofds->fdin != -1)
	{
		if (dup2(iofds->fdin, STDIN_FILENO) == -1)
			print_errmsg("dup2", iofds->infile, strerror(errno), 0);
	}
	if (iofds->fdout != -1)
	{
		if (dup2(iofds->fdout, STDOUT_FILENO) == -1)
			print_errmsg("dup2", iofds->outfile, strerror(errno), 0);
	}
	return ;
}
