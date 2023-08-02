/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpetros <tpetros@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 14:29:59 by tpetros           #+#    #+#             */
/*   Updated: 2023/08/02 12:47:20 by tpetros          ###   ########.fr       */
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

static int	is_invalid_key(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isalpha(str[i]) || str[i] == '_' || str[i] == '!')
			i++;
		else
			return (0);
	}
	return (i);
}

int	ft_unset(t_data *data, t_cmd *cmd)
{
	int	i;
	int	code;

	i = 1;
	code = EXIT_SUCCESS;
	while (cmd->cmdarg[i])
	{
		if (is_invalid_key(cmd->cmdarg[i]) == 0)
		{
			printf("minishell: unset: `%s': not a valid identifier\n",
				cmd->cmdarg[i]);
			code = EXIT_FAILURE;
		}
		else
			ft_del_envv(&data->envar, cmd->cmdarg[i]);
		i++;
	}
	return (code);
}
