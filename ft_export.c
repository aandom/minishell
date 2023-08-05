/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpetros <tpetros@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 15:24:24 by tpetros           #+#    #+#             */
/*   Updated: 2023/08/06 00:32:19 by tpetros          ###   ########.fr       */
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
	if (!(ft_isalpha(str[i]) || str[i] == '_'))
		return (0);
	i++;
	while (str[i])
	{
		if (ft_isalnum(str[i]) || str[i] == '_' || str[i] == '!')
			i++;
		else
			return (0);
	}
	return (i);
}

void	ft_putendl_fd2(char *str, int fd)
{
	size_t	i;
	int		flag;

	if (str)
	{
		flag = 0;
		i = 0;
		while (str[i])
		{
			if (flag == 0 && str[i - 1] == '=')
			{
				write(fd, "\"", 1);
				flag = 1;
			}
			write(fd, &str[i], 1);
			i++;
		}
		if (str[i] == '\0')
			write(fd, "\"", 1);
		write(fd, "\n", 1);
	}
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
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putendl_fd2(tab[i], STDOUT_FILENO);
		i++;
	}
}

int	ft_export(t_data *d)
{
	int		i;
	t_evar	*t;
	int		code;

	i = 1;
	code = EXIT_SUCCESS;
	if (d->cmds->cmdarg[1] != NULL)
	{
		while (d->cmds->cmdarg[i])
		{
			t = new_evar(d->cmds->cmdarg[i]);
			if (is_invalid_key(t->key) == 0)
			{
				print_errmsg(d->cmds->cmd, t->key, "not a valid identifier", 1);
				code = EXIT_FAILURE;
			}
			if (ft_already_exit(d->envar, t->key))
				ft_del_env(&d->envar, t->key);
			add_back_env(&d->envar, t);
			i++;
		}
		env_pointer(d);
	}
	else
		ft_print_export(d);
	return (code);
}
