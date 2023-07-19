/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpetros <tpetros@42abudhabi.student.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 19:31:20 by tpetros           #+#    #+#             */
/*   Updated: 2023/07/15 19:31:30 by tpetros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*join_path(const char *path, const char *bin)
{
	char	*joined;

	joined = ft_strjoin(ft_strjoin(path, "/"), bin);
	return (joined);
}
