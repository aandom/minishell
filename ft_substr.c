/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandom <aandom@student.abudhabi42.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 10:04:14 by aandom            #+#    #+#             */
/*   Updated: 2022/12/22 10:04:14 by aandom           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*result;
	size_t	i;
	size_t	slen;

	if (!s)
		return (NULL);
	i = 0;
	slen = ft_strlen(s);
	// printf("start = [%u]\n", start);
	// printf("str = [%s]\n", s);
	if (slen < len)
	{
		// printf("slen[i] = %lu\n", slen);
		result = (char *) malloc(slen + 1);
	}
	else
	{
		// printf("len[i] = %lu\n", len);
		result = (char *) malloc(len + 1);
	}
	if (!result)
		return (0);
	while ((start < slen) && (i < len && i < slen))
	{
		result[i] = s[start];
		i++;
		start++;
	}
	result[i] = '\0';
	return (result);
}
