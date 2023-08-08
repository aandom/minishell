/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandom <aandom@student.abudhabi42.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 23:14:03 by aandom            #+#    #+#             */
/*   Updated: 2023/06/05 14:43:21 by aandom           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_evar_list(t_evar *head)
{
	t_evar	*tmp;

	if (head == NULL || head->key == NULL)
		return ;
	while (head)
	{
		tmp = head;
		head = head->next;
		if (tmp->key)
			free(tmp->key);
		if (tmp->value)
			free(tmp->value);
		free(tmp);
	}
}

char	**clean(char **av)
{
	int	i;

	i = 0;
	while (av[i] != NULL)
	{
		free(av[i]);
		i++;
	}
	free(av);
	return (0);
}
