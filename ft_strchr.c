/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandom <aandom@student.abudhabi42.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 15:57:26 by aandom            #+#    #+#             */
/*   Updated: 2023/07/21 15:57:26 by aandom           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

char	*ft_strchr(const char *s, int c)
{
	char	*res;

	res = ft_memchr(s, c, ft_strlen(s) + 1);
	return (res);
}