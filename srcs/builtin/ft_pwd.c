/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandom <aandom@student.abudhabi42.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 13:26:14 by tpetros           #+#    #+#             */
/*   Updated: 2024/01/01 17:43:14 by aandom           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtin.h"

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
