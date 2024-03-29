/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envar_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandom <aandom@student.abudhabi42.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 03:18:40 by tpetros           #+#    #+#             */
/*   Updated: 2024/01/01 17:43:14 by aandom           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtin.h"

t_evar	*new_evar(char *str)
{
	t_evar	*newvar;
	int		i;

	newvar = (t_evar *)malloc(sizeof(t_evar));
	if (!newvar)
		return (NULL);
	i = 0;
	newvar->key = extract_key(str, &i);
	newvar->value = extract_value(str);
	newvar->stat = i;
	newvar->next = NULL;
	return (newvar);
}

void	copy_env(t_data *data, char **env)
{
	int		i;
	t_evar	*new;

	i = 0;
	if (data->envar != NULL)
		ft_lst_clear_tvar(&data->envar, voidfree);
	while (env && env[i])
	{
		new = new_evar(env[i]);
		add_back_env(&data->envar, new);
		i++;
	}
}

int	env_var_len(char **env)
{
	int	i;

	i = 0;
	while (env && env[i])
		i++;
	return (i);
}

t_evar	*find_evar(t_evar *env, char *key)
{
	t_evar	*tmp;

	tmp = env;
	while (tmp != NULL)
	{
		if (tmp->key && strcmp(tmp->key, key) == 0)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}
