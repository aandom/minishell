/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandom <aandom@student.abudhabi42.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 13:30:01 by tpetros           #+#    #+#             */
/*   Updated: 2023/08/13 03:20:54 by aandom           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_is_space(char c)
{
	if ((c >= 9 && c <= 13) || c == ' ')
		return (1);
	else
		return (0);
}

int	ft_set_sign(const char *str, int i, int *sign)
{
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			*sign = -1;
		return (1);
	}
	return (0);
}

int	ft_atoi(const char *str)
{
	int		sign;
	int		i;
	long	number;
	int		c;

	sign = 1;
	i = 0;
	number = 0;
	c = 0;
	while (ft_is_space(str[i]))
		i++;
	i = i + ft_set_sign(str, i, &sign);
	while (str[i] == '0')
		i++;
	if (str[i] == '\0')
		return (0);
	while (ft_isdigit(str[i]))
	{
		number = number * 10 + str[i] - '0';
		c++;
		i++;
	}
	if (sign * number > 2147483647 || sign * number < -2147483648 || c > 10)
		return (0);
	return ((int )(number * sign));
}
