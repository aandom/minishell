/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpetros <tpetros@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 13:26:14 by tpetros           #+#    #+#             */
/*   Updated: 2023/07/21 13:26:15 by tpetros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_pwd()
{
	char	buff[PATH_MAX];

	if (getcwd(buff, PATH_MAX))
		printf("%s\n", buff);
	else
		printf("Couldn't retrieve path");
}
