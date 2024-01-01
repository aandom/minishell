/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandom <aandom@student.abudhabi42.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 22:49:10 by aandom            #+#    #+#             */
/*   Updated: 2023/08/07 22:49:10 by aandom           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parse.h"

int	is_next_char_sep(char *str, int i)
{
	if (str && (str[i] == ' ' || str[i] == '$' || str[i] == '='
			|| str[i] == '\0'))
		return (1);
	return (0);
}

int	var_len(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i] && str[i] != '$')
		i++;
	i++;
	if (ft_isdigit(str[i]) || str[i] == '?')
		return (count + 1);
	while (str[i])
	{
		if (ft_isalnum(str[i]) || str[i] == '-')
		{
			i++;
			count++;
		}
		else
			break ;
	}
	return (count);
}

char	*get_varname(char *str)
{
	int		start;
	int		len;
	char	*varname;

	start = 0;
	while (str[start])
	{
		if (str[start] == '$')
		{
			start = start + 1;
			break ;
		}
		start++;
	}
	len = var_len(str);
	varname = ft_substr(str, start, len);
	if (!varname)
		return (NULL);
	return (varname);
}
