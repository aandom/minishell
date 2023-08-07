/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandom <aandom@student.abudhabi42.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 19:30:37 by aandom            #+#    #+#             */
/*   Updated: 2023/08/07 19:30:37 by aandom           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_back_cmd(t_cmd **cmds, t_cmd *cmd)
{
	t_cmd	*tmp;

	tmp = *cmds;
	if (tmp == NULL)
	{
		*cmds = cmd;
		return ;
	}
	if (cmds && *cmds && cmd)
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = cmd;
		cmd->prev = tmp;
	}
	return ;
}

t_cmd	*new_cmd(int pipeout)
{
	t_cmd	*new;

	new = (t_cmd *)malloc(sizeof(t_cmd));
	if (!new)
		return (NULL);
	ft_memset(new, 0, sizeof(t_cmd));
	new->cmd = NULL;
	new->cmdarg = NULL;
	new->path = NULL;
	new->pipeout = pipeout;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

t_cmd	*get_last_cmd(t_cmd *cmd)
{
	t_cmd	*tmp;

	tmp = cmd;
	if (!tmp)
		return (NULL);
	while (cmd->next != NULL)
		cmd = cmd->next;
	return (cmd);
}
