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

#include "minishell.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len;
	char	*result;
	size_t	lens1;
	size_t	lens2;

	if (!s1 && !s2)
		return (NULL);
	if (!s1 && s2)
		return (ft_strdup(s2));
	if (s1 && !s2)
		return (ft_strdup(s1));
	lens1 = ft_strlen(s1);
	lens2 = ft_strlen(s2);
	len = lens1 + lens2;
	result = (char *) malloc((len + 1) * sizeof(char));
	if (!result)
		return (NULL);
	ft_memcpy(result, (char *)s1, (lens1 + 1));
	ft_memcpy (result + lens1, (char *) s2, lens2 + 1);
	return (result);
}