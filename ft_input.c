/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_input.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandom <aandom@student.abudhabi42.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 17:22:42 by aandom            #+#    #+#             */
/*   Updated: 2023/07/08 17:22:42 by aandom           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_read_from(t_cmd **cmds, t_lexer **token)
{
	t_cmd		*lastcmd;
	t_lexer		*tmp;
	t_iofiles	*iofds;
	int			fd;

	tmp = *token;
	lastcmd = get_last_cmd(*cmds);
	initialize_iofds(lastcmd);
	iofds = lastcmd->iofiles;
	if (!remove_prev_iofds(iofds, 1))
		return ;
	iofds->infile = ft_strdup(tmp->next->str);
	fd = open(iofds->infile, O_RDONLY);
	if (fd == -1)
	{
		print_errmsg(iofds->infile, NULL, strerror(errno), 1);
		while (tmp->next && tmp->next->type != PIPE)
			tmp = tmp->next;
	}
	iofds->fdin = fd;
	if (tmp->next->next)
		tmp = tmp->next->next;
	else
		tmp = tmp->next;
	*token = tmp;
}
