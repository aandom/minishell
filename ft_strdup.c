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

#include "minishell.h"

char	*ft_strdup(const char *src)
{
	char	*cp_str;
	size_t	len;

	len = ft_strlen(src);
	cp_str = (char *) malloc((len + 1) * sizeof(char));
	if (!cp_str)
		return (0);
	ft_memcpy(cp_str, src, (len + 1));
	return (cp_str);
}
