/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandom <aandom@student.abudhabi42.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 21:21:46 by aandom            #+#    #+#             */
/*   Updated: 2023/08/07 21:21:46 by aandom           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_max(unsigned long long num, int sign, int *is_valid)
{
	if (sign == 1 && num > LONG_MAX)
		*is_valid = 0;
	else if (sign == -1 && num > -(unsigned long)LONG_MIN)
		*is_valid = 0;
	return (*is_valid);
}

int	set_sign(const char *str, int *sign, int i)
{
	int	c;

	c = 0;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			*sign = *sign * -1;
		c++;
	}
	return (c);
}

long long	ft_atoi_lu(char *str, int *is_valid)
{
	unsigned long long	num;
	size_t				i;
	int					sign;

	i = 0;
	sign = 1;
	num = 0;
	while (str[i] && ft_isspace(str[i]))
		i++;
	i = i + set_sign(str, &sign, i);
	while (str[i] && ft_isdigit(str[i]))
	{
		num = (num * 10) + (str[i] - '0');
		if (!check_max(num, sign, is_valid))
			break ;
		i++;
	}
	return (num * sign);
}
