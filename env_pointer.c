/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_pointer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpetros <tpetros@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 15:25:42 by tpetros           #+#    #+#             */
/*   Updated: 2023/07/28 15:25:43 by tpetros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_envlen(t_evar *env)
{
	t_evar	*tmp;
	int		i;

	tmp = env;
	i = 0;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

void	env_pointer(t_data *data)
{
	int		env_len;
	t_evar	*tmp;
	int		i;

	if (data->env)
		clean(data->env);
	env_len = ft_envlen(data->envar);
	tmp = data->envar;
	i = 0;
	data->env = (char **) malloc(sizeof(char *) * (env_len + 1));
	while (tmp && i < env_len)
	{
		data->env[i] = ft_strjoin(ft_strjoin(tmp->key, "="), tmp->value);
		i++;
		tmp = tmp->next;
	}
}
