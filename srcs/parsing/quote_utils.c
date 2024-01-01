/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandom <aandom@student.abudhabi42.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 22:13:49 by aandom            #+#    #+#             */
/*   Updated: 2023/08/07 22:13:49 by aandom           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parse.h"

int	inside_quote(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (check_quote(str, i, NOQUOTE) == SINGLE || \
			check_quote(str, i, NOQUOTE) == DOUBLE)
		{
			return (1);
		}
		i++;
	}
	return (0);
}

int	is_quote(t_lexer **token, int i)
{
	char	c;

	c = (*token)->str[i];
	if ((c == '\'' || c == '\"') && (*token)->quote == NOQUOTE)
		return (1);
	return (0);
}

int	count_len(char *s, int i, int c)
{
	int	sta;

	sta = NOQUOTE;
	while (s && s[i])
	{
		if ((s[i] == '\'' || s[i] == '\"') && sta == NOQUOTE)
		{
			if (s[i] == '\'')
				sta = SINGLE;
			else if (s[i] == '\"')
				sta = DOUBLE;
			i++;
			continue ;
		}
		if ((s[i] == '\'' && sta == SINGLE) || (s[i] == '\"' && sta == DOUBLE))
		{
			sta = NOQUOTE;
			i++;
			continue ;
		}
		c++;
		i++;
	}
	return (c);
}
