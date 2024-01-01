/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandom <aandom@student.abudhabi42.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 09:41:26 by aandom            #+#    #+#             */
/*   Updated: 2023/08/02 09:41:26 by aandom           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

int	errmsg(char *cmd, char *info, char *errmsg, int errnum)
{
	char	*message;

	message = ft_strdup("minishell: ");
	if (cmd != NULL)
	{
		message = ft_strjoin(message, cmd);
		message = ft_strjoin(message, ": ");
	}
	if (info != NULL)
	{
		message = ft_strjoin(message, info);
		message = ft_strjoin(message, ": ");
	}
	message = ft_strjoin(message, errmsg);
	ft_putendl_fd(message, STDERR_FILENO);
	free(message);
	return (errnum);
}

void	ft_errmsg(char *msg, char *info, int quote)
{
	char	*message;

	message = ft_strdup("minishell: ");
	message = ft_strjoin(message, msg);
	if (info != NULL)
		message = ft_strjoin(message, info);
	if (quote == SINGLE)
		message = ft_strjoin(message, "\'");
	else if (quote == DOUBLE)
		message = ft_strjoin(message, "\"");
	if (quote != NOQUOTE)
		message = ft_strjoin(message, "\'");
	ft_putendl_fd(message, STDERR_FILENO);
	voidfree(message);
}
