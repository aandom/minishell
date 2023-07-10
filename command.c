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

char **copyargs ()
{
	return (NULL);
}

void	fill_cmd_args(t_lexer **token, t_cmd **lastcmd)
{
	t_lexer	*tmp;
	t_lexer *tmp2;
	t_lexer *tmp3;
	char	**newargs;
	int		i;
	int		len;

	i = 0;
	len = 0;
	tmp = *token;
	tmp2 = *token;
	while (tmp->type == WORD)
	{
		len++;
		if (tmp->next->type == END)
			tmp3 = tmp;
		tmp = tmp->next;
	}
	printf("token = %s\n", tmp->str);
	while((*lastcmd)->cmdarg && (*lastcmd)->cmdarg[i])
		i++;
	newargs = malloc(sizeof(char *) * (len + i + 1));
	if (!newargs)
		return ;
	i = 0;
	while ((*lastcmd)->cmdarg && (*lastcmd)->cmdarg[i])
	{
		newargs[i] = ft_strdup((*lastcmd)->cmdarg[i]);
		i++;
	}
	while (len > 0 && (tmp2 && tmp2->type == WORD))
	{
		newargs[i] = ft_strdup(tmp2->str);
		tmp2 = tmp2->next;
		len--;
		i++;
	}
	newargs[i] = NULL;
	i = 0;
	while ( (*lastcmd)->cmdarg && (*lastcmd)->cmdarg[i])
	{
		free((*lastcmd)->cmdarg[i]);
		i++;
	}
	free((*lastcmd)->cmdarg);
	(*lastcmd)->cmdarg = newargs;
	// if (!tmp2)
	// 	*token = tmp2;
	// else
	*token = tmp;
}

void	word_as_cmd(t_cmd **cmds, t_lexer **token)
{
	t_cmd	*lastcmd;
	t_cmd	*new;
	t_lexer	*tmp;
	
	tmp = *token;
	
	while (tmp->type == WORD)
	{
		lastcmd = get_last_cmd(*cmds);
		if (tmp->prev == NULL || tmp->prev->type == PIPE || tmp->prev->prev->type == LESS || tmp->prev->prev->type == LESS_LESS)
		{
			if (lastcmd == NULL || lastcmd->cmd == NULL)
				lastcmd->cmd = ft_strdup(tmp->str);
			else
			{
				new = new_cmd(0);
				new->cmd = ft_strdup(tmp->str);
				add_back_cmd(cmds, new);
				lastcmd = get_last_cmd(*cmds);
			}
		}
		fill_cmd_args(&tmp, &lastcmd);
	}
	*token = tmp;
}

void	no_args_cmds(t_data *data)
{
	
}


void	ft_redirect(t_cmd **cmds, t_lexer **token)
{
	
}

void	ft_append(t_cmd **cmds, t_lexer **token)
{
	
}


void	extract_command(t_data *data, t_lexer *lexed)
{
	t_lexer	*tmp;
	
	tmp = lexed;
	while (tmp->next != NULL)
	{
		if (tmp == lexed)
			add_back_cmd(&data->cmds, new_cmd(0));
		if (tmp->type == WORD)
			word_as_cmd(&data->cmds, &tmp);
		else if (tmp->type == LESS_LESS)
			ft_heredoc(data, &data->cmds, &tmp);
		else if (tmp->type == LESS)
			ft_read_from(data, &data->cmds, &tmp);
		// else if (tmp->type == GREAT_GREAT)
		// 	ft_append(&data->cmds, &tmp);
		// else if (tmp->type == GREAT)
		// 	ft_redirect(&data->cmds, &tmp);
		else if (tmp->type == END)
			break;
		else
		{
			printf("I am here\n");	
			tmp = tmp->next;
		}
	}
	no_args_cmds(data);
}