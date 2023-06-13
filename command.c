/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandom <aandom@student.abudhabi42.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 19:52:44 by aandom            #+#    #+#             */
/*   Updated: 2023/06/13 19:19:42 by aandom           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_back_cmd(t_cmd **cmds, t_cmd *cmd)
{
	t_cmd	*tmp;

	tmp = *cmds;
	if (!)
	
}





void	extract_command(t_data *data, t_lexer *lexed)
{
	t_lexer	*tmp;
	
	tmp = lexed;
	while (tmp->next != NULL)
	{
		if (tmp == lexed)
			add_back_cmd(&data->cmds, new_cmd(NULL));
		if (tmp->type == WORD)
			word_as_cmd(&data->cmds, &tmp);
		else if (tmp->type == LESS_LESS)
			ft_heredoc(&data->cmds, &tmp);
		else if (tmp->type == GREAT_GREAT)
			ft_append(&data->cmds, &tmp);
		else if (tmp->type == GREAT)
			ft_redirect(&data->cmds, &tmp);
		else if (tmp->type == LESS)
			ft_read_from(&data->cmds, &tmp);
		else if (tmp->type == END)
			break;
	}
	fill_args_for_cmds(data);
}