/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandom <aandom@student.abudhabi42.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 21:17:48 by aandom            #+#    #+#             */
/*   Updated: 2023/07/15 21:17:48 by aandom           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

void	ft_pipe(t_data *data, t_cmd **cmds, t_lexer **token)
{
	t_cmd	*lastcmd;
	t_lexer	*tmp;

	(void) data;
	tmp = *token;
	lastcmd = get_last_cmd(*cmds);
	if (lastcmd->cmd == NULL)
		lastcmd->cmd = ft_strdup("");
	lastcmd->pipeout = 1;
	tmp = tmp->next;
	add_back_cmd(&data->cmds, new_cmd(0));
	*token = tmp;
}

int	create_pipes(t_data *data)
{
	int		*tube;
	t_cmd	*cmds;

	cmds = data->cmds;
	while (cmds)
	{
		if (cmds->pipeout || (cmds->prev && cmds->prev->pipeout))
		{
			tube = malloc(sizeof(int) * 2);
			if (!tube || pipe(tube) != 0)
			{
				free_all(data, 0);
				return (0);
			}
			cmds->tube = tube;
		}
		cmds = cmds->next;
	}
	return (1);
}

void	close_unused_pipes(t_cmd *headcmd, t_cmd *curcmd)
{
	while (headcmd)
	{
		if (headcmd != curcmd && headcmd->tube)
		{
			close(headcmd->tube[0]);
			close(headcmd->tube[1]);
			if (headcmd->iofiles)
			{
				if (headcmd->iofiles->fdin != -1)
					close(headcmd->iofiles->fdin);
				if (headcmd->iofiles->fdout != -1)
					close (headcmd->iofiles->fdout);
			}
		}
		headcmd = headcmd->next;
	}
	return ;
}

void	dup_pipe_fds(t_cmd *headcmd, t_cmd *curcmd)
{
	if (!curcmd)
		return ;
	if (curcmd->prev && curcmd->prev->pipeout)
		dup2(curcmd->prev->tube[0], STDIN_FILENO);
	if (curcmd->pipeout)
		dup2(curcmd->tube[1], STDOUT_FILENO);
	close_unused_pipes(headcmd, curcmd);
	return ;
}
