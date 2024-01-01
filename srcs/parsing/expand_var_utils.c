/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandom <aandom@student.abudhabi42.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 23:51:07 by aandom            #+#    #+#             */
/*   Updated: 2023/08/07 23:51:07 by aandom           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parse.h"

char	*copy_token_str(char *str, char *value, int index, int len)
{
	char	*newstr;
	int		i;
	int		j;
	int		m;

	i = 0;
	j = 0;
	m = 0;
	newstr = (char *)malloc(sizeof(char) * len + 1);
	if (!newstr)
		return (NULL);
	while (str[i])
	{
		if (i == index && str[i] == '$')
		{
			i = i + var_len(str + index) + 1;
			while (value[m])
				newstr[j++] = value[m++];
			if (str[i] == '\0')
				break ;
		}
		newstr[j++] = str[i++];
	}
	newstr[j] = '\0';
	return (newstr);
}

void	update_var(t_lexer **token, char *str, int index, char *value)
{
	char	*newstr;
	int		len;

	len = ft_strlen(str) - var_len(str + index) + ft_strlen(value);
	newstr = copy_token_str(str, value, index, len);
	free((*token)->str);
	(*token)->str = newstr;
	return ;
}
