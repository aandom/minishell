/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_new_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandom <aandom@student.abudhabi42.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 18:25:54 by aandom            #+#    #+#             */
/*   Updated: 2024/01/01 17:43:14 by aandom           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtin.h"

static char	**realloc_env(t_data *data, int size)
{
	char	**new_env;
	int		i;

	new_env = ft_calloc(size + 1, sizeof * new_env);
	if (!new_env)
		return (NULL);
	i = 0;
	while (data->env && data->env[i] && i < size)
	{
		new_env[i] = ft_strdup(data->env[i]);
		voidfree(data->env[i]);
		i++;
	}
	free(data->env);
	data->env = NULL;
	return (new_env);
}

int	get_var_ndex(char **env, char *var)
{
	int		i;
	char	*tmp;

	tmp = ft_strjoin(ft_strdup(var), "=");
	if (!tmp)
		return (-1);
	i = 0;
	while (env && env[i])
	{
		if (ft_strncmp(tmp, env[i], ft_strlen(tmp)) == 0)
		{
			voidfree(tmp);
			return (i);
		}
		i++;
	}
	voidfree(tmp);
	return (-1);
}

int	set_env_var(t_data *data, char *key, char *value)
{
	int		idx;
	char	*tmp;

	idx = get_var_ndex(data->env, key);
	if (value == NULL)
		value = "";
	tmp = ft_strjoin(ft_strdup ("="), value);
	if (!tmp)
		return (0);
	if (idx != -1 && data->env[idx])
	{
		voidfree(data->env[idx]);
		data->env[idx] = ft_strjoin(ft_strdup(key), tmp);
	}
	else
	{
		idx = env_var_len(data->env);
		data->env = realloc_env(data, idx + 1);
		if (!data->env)
			return (0);
		data->env[idx] = ft_strjoin(ft_strdup(key), tmp);
	}
	return (voidfree(tmp), 1);
}

char	*get_env_var_value(char **env, char *var)
{
	int		i;
	char	*tmp;

	tmp = ft_strjoin(ft_strdup(var), "=");
	if (!tmp)
		return (NULL);
	i = 0;
	while (env && env[i])
	{
		if (ft_strncmp(tmp, env[i], ft_strlen(tmp) + 1) == 0)
		{
			voidfree(tmp);
			return (ft_strchr(env[i], '=') + 1);
		}
		i++;
	}
	voidfree(tmp);
	return (NULL);
}

void	update_wds(t_data *data, char *wd)
{
	set_env_var(data, "OLDPWD", get_env_var_value(data->env, "PWD"));
	set_env_var(data, "PWD", wd);
	free_evar_list(&data->envar);
	copy_env(data, data->env);
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
}
