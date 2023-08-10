/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpetros <tpetros@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 20:27:33 by tpetros           #+#    #+#             */
/*   Updated: 2023/08/08 21:02:08 by tpetros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	all_n(char *str)
{
	int	i;

	i = 1;
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	ft_echo(t_cmd *cmd)
{
	int	n_flag;
	int	i;

	i = 1;
	n_flag = 0;
	while (cmd->cmdarg[i] && (!ft_strncmp(cmd->cmdarg[i], "-n", 2)
			&& all_n(cmd->cmdarg[i])))
	{
		n_flag = 1;
		i++;
	}
	while (cmd->cmdarg[i])
	{
		ft_putstr_fd(cmd->cmdarg[i], STDOUT_FILENO);
		if (cmd->cmdarg[i + 1] && cmd->cmdarg[i][0] != '\0')
			ft_putstr_fd(" ", STDOUT_FILENO);
		i++;
	}
	if (n_flag != 1)
		ft_putendl_fd("", STDOUT_FILENO);
	return (EXIT_SUCCESS);
}
