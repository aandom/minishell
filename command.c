/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandom <aandom@student.abudhabi42.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 19:52:44 by aandom            #+#    #+#             */
/*   Updated: 2023/07/01 15:48:21 by aandom           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	word_as_cmd(t_cmd **cmds, t_lexer **token)
{
	t_cmd	*lastcmd;
	t_cmd	*new;
	t_lexer	*t;

	t = *token;
	while (t->type == WORD)
	{
		lastcmd = get_last_cmd(*cmds);
		if (t->prev == NULL || (t->prev && t->prev->type == PIPE)
			|| lastcmd->cmd == NULL)
		{
			if (lastcmd == NULL || lastcmd->cmd == NULL)
				lastcmd->cmd = ft_strdup(t->str);
			else
			{
				new = new_cmd(0);
				new->cmd = ft_strdup(t->str);
				add_back_cmd(cmds, new);
				lastcmd = get_last_cmd(*cmds);
			}
		}
		fill_cmd_args(&t, &lastcmd);
	}
	*token = t;
}

void	no_args_cmds(t_data *data)
{
	t_cmd	*cmds;

	if (!data || data->cmds)
		return ;
	cmds = data->cmds;
	while (cmds && cmds->cmd)
	{
		if (!cmds->cmdarg)
		{
			cmds->cmdarg = (char **)malloc(sizeof(char *) * 2);
			cmds->cmdarg[0] = ft_strdup(cmds->cmd);
			cmds->cmdarg[1] = NULL;
		}
		cmds = cmds->next;
	}
}

void	extract_command(t_data *data, t_lexer *lexed)
{
	t_lexer	*tmp;

	tmp = lexed;
	while (tmp && tmp->next != NULL)
	{
		if (tmp == lexed)
			add_back_cmd(&data->cmds, new_cmd(0));
		if (tmp->type == WORD)
			word_as_cmd(&data->cmds, &tmp);
		else if (tmp->type == LESS_LESS)
			ft_heredoc(data, &data->cmds, &tmp);
		else if (tmp->type == LESS)
			ft_read_from(&data->cmds, &tmp);
		else if (tmp->type == GREAT_GREAT)
			ft_append(&data->cmds, &tmp);
		else if (tmp->type == GREAT)
			ft_redirect(&data->cmds, &tmp);
		else if (tmp->type == PIPE)
			ft_pipe(data, &data->cmds, &tmp);
		else if (tmp->type == END)
			break ;
	}
	return ;
}
