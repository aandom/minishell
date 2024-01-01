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

#include "../../includes/parse.h"

void	ft_append(t_cmd **cmds, t_lexer **token)
{
	t_cmd		*lastcmd;
	t_lexer		*tmp;
	t_iofiles	*iofds;
	int			fd;

	tmp = *token;
	lastcmd = get_last_cmd(*cmds);
	initialize_iofds(lastcmd);
	iofds = lastcmd->iofiles;
	if (remove_prev_iofds(iofds, 2))
	{
		iofds->outfile = ft_strdup(tmp->next->str);
		fd = open(iofds->outfile, O_WRONLY | O_APPEND | O_CREAT, 0664);
		if (fd == -1)
			errmsg(iofds->outfile, NULL, strerror(errno), 1);
		iofds->fdout = fd;
	}
	if (tmp->next && tmp->next->next)
		tmp = tmp->next->next;
	else
		tmp = tmp->next;
	*token = tmp;
}

void	ft_redirect(t_cmd **cmds, t_lexer **token)
{
	t_cmd		*lastcmd;
	t_lexer		*tmp;
	t_iofiles	*iofds;
	int			fd;

	tmp = *token;
	lastcmd = get_last_cmd(*cmds);
	initialize_iofds(lastcmd);
	iofds = lastcmd->iofiles;
	if (remove_prev_iofds(iofds, 2))
	{
		iofds->outfile = ft_strdup(tmp->next->str);
		fd = open(iofds->outfile, O_WRONLY | O_TRUNC | O_CREAT, 0664);
		if (fd == -1)
			errmsg(iofds->outfile, NULL, strerror(errno), 1);
		iofds->fdout = fd;
	}
	if (tmp->next && tmp->next->next)
		tmp = tmp->next->next;
	else
		tmp = tmp->next;
	*token = tmp;
}
