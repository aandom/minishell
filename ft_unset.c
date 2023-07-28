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

#include "minishell.h"


void	ft_del_envv(t_evar **head, char *str)
{
	t_evar	*temp;
	t_evar	*prev;

    if (!head || !*head || !str)
        return ;
    temp = *head;
	prev = NULL;
    if (temp != NULL && ft_strncmp(temp->key, str, ft_strlen(str)) == 0)
    {
        *head = temp->next;
        free(temp->key);
        free(temp->value);
        free(temp);
        return;
    }
    while (temp != NULL && ft_strncmp(temp->key, str, ft_strlen(str)) != 0)
    {
        prev = temp;
        temp = temp->next;
    }
    if (temp == NULL)
        return ;
    prev->next = temp->next;
    free(temp->key);
    free(temp->value);
    free(temp);
}

void	ft_unset(t_data *data, t_cmd *cmd)
{
	int	i;

	i = 1;
	while (cmd->cmdarg[i])
	{
		ft_del_envv(&data->envar, cmd->cmdarg[i]);
		i++;
	}
	ft_env((data)->envar);
}
