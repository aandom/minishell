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

#include "../../includes/utils.h"

void	free_evar_list(t_evar **head)
{
	t_evar	*tmp;

	while (*head)
	{
		tmp = (*head)->next;
		if ((*head)->key)
			free((*head)->key);
		if ((*head)->value)
			free((*head)->value);
		free(*head);
		*head = tmp;
	}
}

static void	ft_delone_tvar(t_evar *lst, void (*del) (void *))
{
	if (lst->key)
		(*del)(lst->key);
	if (lst->value)
		(*del)(lst->value);
}

void	ft_lst_clear_tvar(t_evar **lst, void (*del)(void*))
{
	t_evar	*m;

	if (lst && del && lst)
	{
		while (*lst)
		{
			m = (*lst)->next;
			ft_delone_tvar(*lst, del);
			free(*lst);
			*lst = m;
		}
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
