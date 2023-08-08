/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shlvl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpetros <tpetros@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 20:09:52 by tpetros           #+#    #+#             */
/*   Updated: 2023/08/08 20:53:38 by tpetros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_current_shlvl(t_evar *env)
{
	t_evar	*tmp;
	int		sh_lvl;

	tmp = env;
	sh_lvl = 0;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, "SHLVL") == 0)
			sh_lvl = ft_atoi(tmp->value);
		tmp = tmp->next;
	}
	return (sh_lvl);
}

void	ft_shlvl(t_data *data, t_evar *env)
{
	int		sh_lvl;
	t_evar	*tmp;
	char	*shl;
	char	*hold;

	tmp = env;
	sh_lvl = ft_current_shlvl(tmp) + 1;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, "SHLVL") == 0)
		{
			ft_del_env(&env, "SHLVL");
			break ;
		}
		tmp = tmp->next;
	}
	shl = ft_itoa(sh_lvl);
	hold = ft_strdup("SHLVL=");
	hold = ft_strjoin(hold, shl);
	add_back_env(&env, new_evar(hold));
	free(shl);
	free(hold);
	env_pointer(data);
}
