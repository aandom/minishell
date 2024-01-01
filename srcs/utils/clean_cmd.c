/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_new.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandom <aandom@student.abudhabi42.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 06:05:56 by aandom            #+#    #+#             */
/*   Updated: 2023/07/26 06:05:56 by aandom           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

void	voidfree(void *ptr)
{
	if (ptr != NULL)
	{
		free(ptr);
		ptr = NULL;
	}
	return ;
}

static void	ft_delone_cmd(t_cmd *lst, void (*del) (void *))
{
	if (lst->cmd)
		(*del)(lst->cmd);
	if (lst->tube)
		(*del)(lst->tube);
	if (lst->cmdarg)
		ft_arr_freer(lst->cmdarg);
	if (lst->iofiles)
		ft_free_iofile(lst->iofiles);
}

void	ft_lst_clear_cmd(t_cmd **lst, void (*del)(void*))
{
	t_cmd	*m;

	if (lst && del && lst)
	{
		while (*lst)
		{
			m = (*lst)->next;
			ft_delone_cmd(*lst, del);
			free(*lst);
			*lst = m;
		}
	}
}
