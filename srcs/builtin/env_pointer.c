/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_pointer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandom <aandom@student.abudhabi42.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 15:25:42 by tpetros           #+#    #+#             */
/*   Updated: 2024/01/01 17:43:14 by aandom           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtin.h"

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

int	clear_env(t_data *data)
{
	if (data->env != NULL)
		ft_arr_freer(data->env);
	if (!data->envar)
	{
		data->env = NULL;
		return (0);
	}
	return (1);
}

void	env_pointer(t_data *data)
{
	int		env_len;
	t_evar	*tmp;
	int		i;
	char	*holder;

	if (!clear_env(data))
		return ;
	env_len = ft_envlen(data->envar);
	tmp = data->envar;
	i = 0;
	data->env = (char **) malloc(sizeof(char *) * (env_len + 1));
	if (!data->env)
		return ;
	while (tmp && i < env_len)
	{
		holder = ft_strjoin(ft_strdup(tmp->key), "=");
		data->env[i] = ft_strjoin(holder, tmp->value);
		i++;
		tmp = tmp->next;
	}
	data->env[i] = NULL;
}

void	sort_env(char **tab, int env_len)
{
	int		ordered;
	int		i;
	char	*tmp;

	ordered = 0;
	while (tab && ordered == 0)
	{
		ordered = 1;
		i = 0;
		while (i < env_len - 1)
		{
			if (ft_strcmp(tab[i], tab[i + 1]) > 0)
			{
				tmp = tab[i];
				tab[i] = tab[i + 1];
				tab[i + 1] = tmp;
				ordered = 0;
			}
			i++;
		}
		env_len--;
	}
}
