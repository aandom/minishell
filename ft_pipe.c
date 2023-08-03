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

#include "minishell.h"

void	ft_pipe(t_data *data, t_cmd **cmds, t_lexer **token)
{
	t_cmd	*lastcmd;
	t_lexer	*tmp;

	tmp = *token;
	lastcmd = get_last_cmd(*cmds);
	lastcmd->pipeout = 1;
	tmp = tmp->next;
	*token = tmp;
}
