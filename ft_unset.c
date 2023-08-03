/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpetros <tpetros@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 14:29:59 by tpetros           #+#    #+#             */
/*   Updated: 2023/08/03 18:28:20 by tpetros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_invalid_key(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isalpha(str[i]) || str[i] == '_' || str[i] == '!')
			i++;
		else
			return (0);
	}
	return (i);
}

int	ft_unset(t_data *data, t_cmd *cmd)
{
	int	i;
	int	code;

	i = 1;
	code = EXIT_SUCCESS;
	while (cmd->cmdarg[i])
	{
		if (is_invalid_key(cmd->cmdarg[i]) == 0)
		{
			printf("minishell: unset: `%s': not a valid identifier\n",
				cmd->cmdarg[i]);
			code = EXIT_FAILURE;
		}
		else
			ft_del_env(&data->envar, cmd->cmdarg[i]);
		i++;
	}
	return (code);
}
