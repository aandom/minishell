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

char	*ft_strtrim(const char *s1, const char *set)
{
	size_t	left;
	size_t	right;

	if (!(s1) || !(set))
		return (NULL);
	left = 0;
	right = ft_strlen(s1) - 1;
	while (s1[left] && ft_strchr(set, s1[left]))
	{
		left++;
	}
	while (s1[right] && ft_strrchr(set, s1[right]) && (right > left))
	{
		right--;
	}
	return (ft_substr(s1, left, right - left + 1));
}
