/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandom <aandom@student.abudhabi42.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 09:53:25 by aandom            #+#    #+#             */
/*   Updated: 2022/12/22 09:53:25 by aandom           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	char	*cp_str;
	size_t	len;

	len = ft_strlen(src) + 1;
	cp_str = NULL;
	cp_str = malloc(sizeof(char) * len);
	if (!cp_str)
		return (0);
	ft_strlcpy(cp_str, src, (len + 1));
	return (cp_str);
}
