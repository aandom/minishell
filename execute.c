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
	if (access(c_exe, F_OK | X_OK) == -1)
		return(print_errmsg(c_exe, NULL, strerror(errno), 126));
	if (execve(c_exe, cmd->cmdarg, data->env) == -1)
		return(print_errmsg("execve", NULL, strerror(errno), errno));
	return (1);
}

int	exec_cmd_with_path(t_data *data, t_cmd *cmd)
{
	int	res;

	res = check_command(cmd);
	if (res != 0)
		return (res);
	if (execve(cmd->cmd, cmd->cmdarg, data->env) == -1)
		return(print_errmsg("execve", NULL, strerror(errno), errno));
	return (1);
}

int	execute_cmd(t_data *data, t_cmd *cmd, t_exno *ex_no)
{
	int	res;

	if (!cmd && !cmd->cmd)
		return (1);
	signal(SIGQUIT, sigquit_handler);
	g_exit_code = IN_CMD;
	if (!ft_check_iofiles(cmd->iofiles))
		exitshell(data, 1);
	dup_pipe_fds(data->cmds, cmd);
	set_iofds(cmd->iofiles);
	close_iofds(data->cmds, 0);
	if (!ft_strchr(cmd->cmd, '/'))
	{
		if (is_builtin(cmd->cmd))
			res = execute_builtin(data, cmd, ex_no);
		else
		{
			res = 127;
			res = exec_cmd_with_nopath(data, cmd);
		}
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
	while (cmds)
	{
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
		g_exit_code = 0;
		return(130);
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
