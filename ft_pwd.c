/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpetros <tpetros@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 13:26:14 by tpetros           #+#    #+#             */
/*   Updated: 2023/08/05 23:16:09 by tpetros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(t_data *data)
{
	char	pwd[MAX_PATH];

	if (data->pwd)
	{
		ft_putendl_fd(data->pwd, STDOUT_FILENO);
		return (EXIT_SUCCESS);
	}
	if (getcwd(pwd, MAX_PATH) != NULL)
	{
		ft_putendl_fd(pwd, STDOUT_FILENO);
		return (EXIT_SUCCESS);
	}
	else
	{
		perror("minishell: pwd: ");
		return (EXIT_FAILURE);
	}
}
