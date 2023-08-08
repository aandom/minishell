/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpetros <tpetros@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 22:17:33 by tpetros           #+#    #+#             */
/*   Updated: 2023/08/08 22:20:41 by tpetros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_already_exit(t_evar *env, char *str)
{
	t_evar	*tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strcmp(str, tmp->key) == 0)
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
		if (str[i] == '\0' && str[i - 1] == '=')
			write(fd, "\"", 1);
		write(fd, "\n", 1);
	}
}
