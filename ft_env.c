/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandom <aandom@student.abudhabi42.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 14:03:25 by tpetros           #+#    #+#             */
/*   Updated: 2023/08/15 00:34:28 by aandom           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_cmd *cmd, t_evar *env)
{
	t_evar	*tmp;

	if (!env)
		return (EXIT_FAILURE);
	if (cmd->cmdarg[1] != NULL)
	{
		errmsg("env", cmd->cmdarg[1], "No such file or directory", 127);
		return (EXIT_FAILURE);
	}
	tmp = env;
	while (tmp)
	{
		if (tmp->stat)
		{
			ft_putstr_fd(tmp->key, STDOUT_FILENO);
			ft_putstr_fd("=", STDOUT_FILENO);
			ft_putendl_fd(tmp->value, STDOUT_FILENO);
		}
		tmp = tmp->next;
	}
	return (EXIT_SUCCESS);
}
