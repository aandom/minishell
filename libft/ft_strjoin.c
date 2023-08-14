/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandom <aandom@student.abudhabi42.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 17:40:01 by aandom            #+#    #+#             */
/*   Updated: 2023/07/06 17:40:01 by aandom           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char	*str_j;
	int		i;
	int		j;
	int		len1;
	int		len2;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	if (!s1)
		s1 = ft_calloc(1, 1);
	if (!s1 && !s2)
		return (s1);
	str_j = (char *)ft_calloc((sizeof(char) * (len1 + len2 + 1)), 1);
	if (!str_j)
		return (0);
	i = -1;
	j = -1;
	while (s1[++i])
		str_j[i] = s1[i];
	while (s2[++j])
		str_j[i++] = s2[j];
	str_j[i] = '\0';
	free(s1);
	return (str_j);
}
