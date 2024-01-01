/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandom <aandom@student.abudhabi42.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 14:29:59 by tpetros           #+#    #+#             */
/*   Updated: 2024/01/01 17:43:14 by aandom           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtin.h"

int	ft_unset(t_data *data, t_cmd *cmd)
{
	int	i;
	int	code;

	i = 1;
	code = EXIT_SUCCESS;
	while (cmd->cmdarg[i])
	{
		if (!is_invalid_key(cmd->cmdarg[i]))
			errmsg("unset", cmd->cmdarg[i], "not a valid identifier", 1);
		ft_del_env(&data->envar, cmd->cmdarg[i]);
		i++;
	}
	env_pointer(data);
	return (code);
}
