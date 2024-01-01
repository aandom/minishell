/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc_delim.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandom <aandom@student.abudhabi42.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 03:25:42 by tpetros           #+#    #+#             */
/*   Updated: 2024/01/01 17:31:52 by aandom           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parse.h"

static int	delim_len(char *str)
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
