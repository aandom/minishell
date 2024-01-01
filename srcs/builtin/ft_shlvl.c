/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shlvl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandom <aandom@student.abudhabi42.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 20:09:52 by tpetros           #+#    #+#             */
/*   Updated: 2024/01/01 17:43:14 by aandom           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtin.h"

int	ft_current_shlvl(t_evar *env)
{
	t_evar	*tmp;
	int		sh_lvl;

	tmp = env;
	sh_lvl = 0;
	tmp = find_evar(env, "SHLVL");
	sh_lvl = ft_atoi(tmp->value);
	return (sh_lvl);
}

void	init_oldpwd(t_evar *env)
{
	t_evar	*tmp;

	tmp = find_evar(env, "OLDPWD");
	if (!tmp)
		add_back_env(&env, new_evar("OLDPWD"));
}

void	ft_shlvl(t_data *data, t_evar *env)
{
	int		sh_lvl;
	t_evar	*tmp;
	char	*shl;
	char	*hold;

	tmp = env;
	tmp = find_evar(env, "SHLVL");
	if (tmp == NULL)
	{
		shl = ft_itoa(1);
		hold = ft_strjoin(ft_strdup("SHLVL="), shl);
		add_back_env(&env, new_evar(hold));
		free(shl);
		free(hold);
	}
	else
	{
		sh_lvl = ft_current_shlvl(tmp) + 1;
		free(tmp->value);
		tmp->value = ft_itoa(sh_lvl);
	}
	init_oldpwd(env);
	env_pointer(data);
}

int	init_wds(t_data *data)
{
	char	buff[MAX_PATH];
	char	*wd;

	wd = getcwd(buff, MAX_PATH);
	data->pwd = ft_strdup(wd);
	if (!data->pwd)
		return (0);
	if (var_in_env(data->envar, "OLDPWD") == 1)
	{
		data->oldpwd = ft_strdup(get_varvalue(data->envar,
					"OLDPWD"));
		if (!data->oldpwd)
			return (0);
	}
	else
	{
		data->oldpwd = ft_strdup(wd);
		if (!data->oldpwd)
			return (0);
	}
	return (1);
}
