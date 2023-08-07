/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wait.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandom <aandom@student.abudhabi42.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 21:09:16 by aandom            #+#    #+#             */
/*   Updated: 2023/08/07 21:09:16 by aandom           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	fork_wait(t_data *data)
{
	pid_t	ch_pid;
	int		status;
	int		res;

	close_iofds(data->cmds, 0);
	res = 0;
	ch_pid = 0;
	while (ch_pid != -1 || errno != ECHILD)
	{
		ch_pid = waitpid(-1, &status, 0);
		if (ch_pid == data->pid)
			res = status;
		continue ;
	}
	if (WIFSIGNALED(res))
		status = 128 + WTERMSIG(res);
	else if (WIFEXITED(res))
		status = WEXITSTATUS(res);
	else
		status = res;
	return (status);
}
