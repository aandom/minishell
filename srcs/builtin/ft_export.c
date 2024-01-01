/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandom <aandom@student.abudhabi42.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 15:24:24 by tpetros           #+#    #+#             */
/*   Updated: 2024/01/01 17:44:39 by aandom           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtin.h"

static void	ft_print_export(t_data *data)
{
	char	**tab;
	int		i;

	sort_env(data->env, ft_envlen(data->envar));
	tab = data->env;
	i = 0;
	while (tab && tab[i])
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putendl_fd2(tab[i], STDOUT_FILENO);
		i++;
	}
}

void	ft_var_freer(t_evar *env)
{
	t_evar	*tmp;

	tmp = env;
	voidfree(tmp->key);
	voidfree(tmp->value);
	voidfree(tmp);
}

int	ft_export_util(t_data *d)
{
	int		i;
	t_evar	*t;

	i = 1;
	while (d->cmds->cmdarg[i])
	{
		t = new_evar(d->cmds->cmdarg[i]);
		if (is_invalid_key(t->key) == 0)
		{
			errmsg(d->cmds->cmd, d->cmds->cmdarg[i], EXP_ERR, 1);
			ft_var_freer(t);
			return (EXIT_FAILURE);
		}
		if (ft_already_exit(d->envar, t->key))
			ft_del_env(&d->envar, t->key);
		add_back_env(&d->envar, t);
		i++;
	}
	env_pointer(d);
	return (EXIT_SUCCESS);
}

int	ft_export(t_data *d)
{
	int		code;

	code = EXIT_SUCCESS;
	if (d->cmds->cmdarg[1] != NULL)
		code = ft_export_util(d);
	else
		ft_print_export(d);
	return (code);
}
