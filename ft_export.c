/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandom <aandom@student.abudhabi42.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 15:24:24 by tpetros           #+#    #+#             */
/*   Updated: 2023/08/04 15:16:35 by aandom           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_already_exit(t_evar *env, char *str)
{
	t_evar	*tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strncmp(str, tmp->key, ft_strlen(str)) == 0)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int	is_invalid_key(char *str)
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

void	ft_print_export(t_data *data)
{
	char	**tab;
	int		i;

	env_pointer(data);
	sort_env(data->env, ft_envlen(data->envar));
	tab = data->env;
	i = 0;
	while (tab[i])
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putendl_fd(tab[i], 1);
		i++;
	}
}

int	ft_export(t_data *d)
{
	int		i;
	t_evar	*tmp;
	int		code;

	i = 1;
	code = EXIT_SUCCESS;
	if (d->cmds->cmdarg[1] != NULL)
	{
		while (d->cmds->cmdarg[i])
		{
			tmp = new_evar(d->cmds->cmdarg[i]);
			if (is_invalid_key(tmp->key) == 0)
			{
				print_errmsg(d->cmds->cmd, tmp->key, "not a valid identifier", 1);
				code = EXIT_FAILURE;
			}
			if (ft_already_exit(d->envar, tmp->key))
				ft_del_env(&d->envar, tmp->key);
			add_back_env(&d->envar, tmp);
			i++;
		}
	}
	else
		ft_print_export(d);
	return (code);
}
