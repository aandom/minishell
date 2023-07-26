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

# include "minishell.h"

void    voidfree(void *ptr)
{
    if (ptr)
    {
        free(ptr);
        ptr = NULL;
    }
    return ;
}

void	ft_delone_token(t_lexer *lst, void (*del)(void*))
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
    // voidfree(lst);
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
			// (*del)((*lst)->content);
			free(*lst);
			*lst = m;
		}
	}
}

void    ft_delone_cmd(t_cmd *lst, void (*del) (void *))
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
			// (*del)((*lst)->content);
			free(*lst);
			*lst = m;
		}
	}
}