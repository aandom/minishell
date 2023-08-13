/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandom <aandom@student.abudhabi42.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 23:30:16 by aandom            #+#    #+#             */
/*   Updated: 2023/07/17 23:30:16 by aandom           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_cmd_helper(t_data *data, t_cmd *cmd, t_exno *ex_no)
{
	int	res;

	if (is_builtin(cmd->cmd))
		res = execute_builtin(data, cmd, ex_no);
	else
	{
		res = 127;
		res = exec_cmd_with_nopath(data, cmd);
	}
	return (res);
}

int	execute_cmd(t_data *data, t_cmd *cmd, t_exno *ex_no)
{
	int	res;

	if (!cmd && !cmd->cmd)
		return (1);
	g_exit_code = IN_CMD;
	if (!ft_check_iofiles(cmd->iofiles))
		exitshell(data, 1);
	dup_pipe_fds(data->cmds, cmd);
	set_iofds(cmd->iofiles);
	close_iofds(data->cmds, 0);
	if (!ft_strchr(cmd->cmd, '/'))
	{
		res = execute_cmd_helper(data, cmd, ex_no);
		if (res != 127)
			exitshell(data, res);
	}
	else
		res = exec_cmd_with_path(data, cmd);
	exitshell(data, res);
	return (res);
}

int	create_forks(t_data *data, t_exno *ex_no)
{
	t_cmd	*cmds;
	int		a;

	cmds = data->cmds;
	while (cmds && data->pid != 0)
	{
		child_signals();
		data->pid = fork();
		if (data->pid == -1)
			return (1);
		else if (data->pid == 0)
			execute_cmd(data, cmds, ex_no);
		cmds = cmds->next;
	}
	a = (fork_wait(data));
	return (a);
}

int	ft_execute(t_data *data, t_exno *ex_no)
{
	int	res;

	if (g_exit_code == STOP_HEREDOC)
	{
		g_exit_code = IN_CMD;
		return (130);
	}
	res = check_prepare_exec(data);
	if (res != 127)
		return (res);
	if (!data->cmds->pipeout && !data->cmds->prev
		&& ft_check_iofiles(data->cmds->iofiles))
	{
		set_iofds(data->cmds->iofiles);
		if (is_builtin(data->cmds->cmd))
			res = execute_builtin(data, data->cmds, ex_no);
		reset_stdio(data->cmds->iofiles);
	}
	if (res != 127)
		return (res);
	return (create_forks(data, ex_no));
}
