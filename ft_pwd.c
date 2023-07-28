/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpetros <tpetros@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 13:26:14 by tpetros           #+#    #+#             */
/*   Updated: 2023/07/21 13:26:15 by tpetros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(t_evar *env)
{
	t_evar	*tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strncmp("PWD", tmp->key, 4) == 0)
		{
			printf("%s\n", tmp->value);
			break ;
		}
		tmp = tmp->next;
	}
}
