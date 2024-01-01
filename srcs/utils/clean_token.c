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

static void	ft_delone_token(t_lexer *lst, void (*del)(void*))
{
	if (lst && del && lst->str)
	{
		(del)(lst->str);
		lst->str = NULL;
	}
	if (lst->prev)
		lst->prev->next = lst->next;
	if (lst->next)
		lst->next->prev = lst->prev;
}

void	ft_lst_clear_token(t_lexer **lst, void (*del)(void*))
{
	t_lexer	*m;

	if (lst && del && lst)
	{
		while (*lst)
		{
			m = (*lst)->next;
			ft_delone_token(*lst, del);
			free(*lst);
			*lst = m;
		}
	}
}
