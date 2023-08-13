/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpetros <tpetros@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 22:21:56 by tpetros           #+#    #+#             */
/*   Updated: 2023/08/08 22:23:08 by tpetros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd(t_evar *env, char *key)
{
	t_evar	*tmp;
	char	oldpwd[MAX_PATH];
	char	*holder;

	tmp = env;
	if (getcwd(oldpwd, MAX_PATH) == NULL)
		return ;
	while (tmp)
	{
		if (tmp->key && ft_strcmp(key, tmp->key) == 0)
		{
			ft_del_env(&env, key);
			holder = ft_strjoin(ft_strjoin(ft_strdup(key), "="), oldpwd);
			add_back_env(&env, new_evar(holder));
			free(holder);
			break ;
		}
		tmp = tmp->next;
	}
}

void	update_pwd(t_data *data, char *key, char *value)
{
	char	*new_env;
	t_evar	*old;

	if (key == NULL || value == NULL)
		return ;
	new_env = ft_strjoin(ft_strdup(key), "=");
	new_env = ft_strjoin(new_env, value);
	(void) data;
	old = find_evar(data->envar, key);
	if (old == NULL && ft_strcmp(key, "OLDPWD") == 0)
	{
		free(new_env);
		return ;
	}
	if (old && !old->value)
	{
		free(old->value);
		old->value = ft_strdup(value);
	}
	else
		add_back_env(&data->envar, new_evar(new_env));
	free(new_env);
}

void	update_wds_env(t_data *data, char *wd)
{
	char	*hold;

	hold = get_varvalue(data->envar, "PWD");
	update_pwd(data, "OLDPWD", hold);
	update_pwd(data, "PWD", wd);
	if (data->oldpwd)
	{
		voidfree(data->oldpwd);
		data->oldpwd = ft_strdup(data->pwd);
	}
	if (data->pwd)
	{
		voidfree(data->pwd);
		data->pwd = ft_strdup(wd);
	}
	voidfree(wd);
	voidfree(hold);
	pwd(data->envar, "PWD");
	env_pointer(data);
}

int	arg_counter(char **cmd)
{
	int	count;

	count = 0;
	while (cmd[count])
		count++;
	return (count);
}
