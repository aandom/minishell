/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandom <aandom@student.abudhabi42.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 19:52:44 by aandom            #+#    #+#             */
/*   Updated: 2023/06/15 19:38:15 by aandom           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_back_cmd(t_cmd **cmds, t_cmd *cmd)
{
	t_cmd	*tmp;

	tmp = *cmds;
	if (!tmp)
		*cmds = cmd;
	else
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = cmd;
	}
	return ;
	
}

t_cmd	*new_cmd(int pipeout)
{
	t_cmd	*new;
	
	new = malloc(sizeof(t_cmd));
	if(!new)
		return (NULL);
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
	while (tmp->next != NULL)
		tmp = tmp->next;
	return (tmp);
}

void	fill_cmd_args(t_lexer **token, t_cmd **lastcmd)
{
		
}

void	word_as_cmd(t_cmd **cmds, t_lexer **token)
{
	t_cmd	*lastcmd;
	t_lexer	*tmp;
	
	tmp = *token;
	while (tmp->type == WORD)
	{
		lastcmd = get_last_cmd(*cmds);
		if (tmp->prev == NULL || tmp->prev->type == PIPE)
		{
			lastcmd->cmd = ft_strdup(tmp->str);
			tmp = tmp->next;
		}
		else
			fill_cmd_args(&tmp, &lastcmd);
	}
}

void	no_args_cmds(t_data *data)
{
	
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
	no_args_cmds(data);
}