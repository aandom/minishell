/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_arg.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandom <aandom@student.abudhabi42.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 19:32:33 by aandom            #+#    #+#             */
/*   Updated: 2023/08/07 19:32:33 by aandom           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_args(t_lexer *token)
{
	int		len;
	t_lexer	*tmp;

	len = 0;
	tmp = token;
	while (tmp && tmp->type == WORD)
	{
		len++;
		tmp = tmp->next;
	}
	return (len);
}

int	copy_cmdarg(char **cmdarg, char **newarg)
{
	int	i;

	i = 0;
	while (cmdarg && cmdarg[i])
	{
		newarg[i] = ft_strdup(cmdarg[i]);
		i++;
	}
	return (i);
}

void	fill_cmd_args(t_lexer **token, t_cmd **lastcmd)
{
	t_lexer	*tmp;
	char	**newargs;
	int		i;
	int		len;

	len = 0;
	tmp = *token;
	len = count_args(tmp) + env_var_len((*lastcmd)->cmdarg);
	newargs = malloc(sizeof(char *) * (len + 1));
	if (!newargs)
		return ;
	i = copy_cmdarg((*lastcmd)->cmdarg, newargs);
	while (i < len && (tmp && tmp->type == WORD))
	{
		newargs[i] = ft_strdup(tmp->str);
		tmp = tmp->next;
		i++;
	}
	newargs[i] = NULL;
	ft_arr_freer((*lastcmd)->cmdarg);
	(*lastcmd)->cmdarg = newargs;
	*token = tmp;
}
