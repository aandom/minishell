/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpetros <tpetros@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 14:29:59 by tpetros           #+#    #+#             */
/*   Updated: 2023/07/21 14:30:00 by tpetros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_del_env(t_evar *env, char *str)
{
    t_evar	*current;
    t_evar	*prev;

	current = env;
    if (current == NULL)
        return ;
    while (current != NULL && ft_strncmp(current->key, str, ft_strlen(current->key)) != 0) 
	{
        prev = current;
        current = current->next;
    }
    if (current == NULL)
        return;
    if (prev == NULL)
        env = current->next;
    else
        prev->next = current->next;
    free(current->key);
	free(current->value);
    free(current);
}


void	ft_unset(t_data *data)
{
	int	i;

	i = 1;
	while (data->cmds->cmdarg[i])
	{
		ft_del_env(data->envar, data->cmd->cmdargs[i]);
		i++;
	}
}
