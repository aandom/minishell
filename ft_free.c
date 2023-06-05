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

// void	ft_clean(t_list **lst)
// {
// 	t_list	*tmp;
// 	t_list	*tmp2;

// 	tmp = *lst;
// 	while (tmp)
// 	{
// 		tmp2 = tmp->next;
// 		free(tmp);
// 		tmp = tmp2;
// 	}
// 	return ;
// }

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
