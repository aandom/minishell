/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_fin_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandom <aandom@student.abudhabi42.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 04:16:47 by aandom            #+#    #+#             */
/*   Updated: 2023/08/15 00:34:42 by aandom           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_cmd_with_nopath(t_data *data, t_cmd *cmd)
{
	char	*c_exe;

	if (!cmd->cmd || cmd->cmd[0] == '\0')
		return (127);
	if (is_directory(cmd->cmd))
		return (127);
	c_exe = get_cmd(data->envar, cmd);
	if (!c_exe)
		return (127);
	if (access(c_exe, F_OK) == -1)
	{
		errmsg(c_exe, NULL, strerror(errno), 127);
		return (free(c_exe), 127);
	}
	if (access(c_exe, F_OK | X_OK) == -1)
	{
		errmsg(c_exe, NULL, strerror(errno), 126);
		return (free(c_exe), 126);
	}
	if (execve(c_exe, cmd->cmdarg, data->env) == -1)
		return (free(c_exe), errmsg("execve", NULL, strerror(errno), errno));
	return (1);
}

int	exec_cmd_with_path(t_data *data, t_cmd *cmd)
{
	int	res;

	res = check_command(cmd);
	if (res != 0)
		return (res);
	if (execve(cmd->cmd, cmd->cmdarg, data->env) == -1)
		return (errmsg("execve", NULL, strerror(errno), errno));
	return (1);
}
