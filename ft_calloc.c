/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpetros <tpetros@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 18:09:00 by tpetros           #+#    #+#             */
/*   Updated: 2023/08/08 18:09:28 by tpetros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	if ((count >= SIZE_MAX && size > 1) || (count > 1 && size > SIZE_MAX))
		return (NULL);
	if (!count || !size)
		return (malloc(count * size));
	ptr = malloc(count * size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, size * count);
	return (ptr);
}
