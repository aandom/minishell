/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandom <aandom@student.abudhabi42.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 10:40:41 by aandom            #+#    #+#             */
/*   Updated: 2022/12/22 10:40:41 by aandom           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strtrim(char const *s1, unsigned char set)
{
	int	lstart;
	int	lend;

	if (!s1 || !set)
		return (NULL);
	lstart = 1;
	lend = ft_strlen((char *)s1);
	return (ft_substr(s1, lstart, lend - 2));
}
