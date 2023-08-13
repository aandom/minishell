/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc_utils2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpetros <tpetros@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 03:25:42 by tpetros           #+#    #+#             */
/*   Updated: 2023/08/13 03:25:44 by tpetros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	delim_len(char *str)
{
	int	i;
	int	c;

	i = -1;
	c = 0;
	while (str[++i])
	{
		if (str[i] != '\'' && str[i] != '\"')
			c++;
	}
	return (c);
}

int	check_update_delimiter(char **delim)
{
	int		i;
	char	*d;
	char	*str;

	i = 0;
	str = *delim;
	if (!ft_strchr(*delim, '\'') && !ft_strchr(*delim, '\"'))
		return (0);
	d = (char *)malloc(sizeof(char) * delim_len(*delim) + 1);
	if (!d)
		return (0);
	while (str && *str)
	{
		if (*str != '\"' && *str != '\'')
		{
			d[i] = *str;
			i++;
		}
		str++;
	}
	d[i] = '\0';
	voidfree(*delim);
	*delim = d;
	return (1);
}
