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

int	execute_nopath_cmd(t_data *data, t_cmd *cmd)
{
	char	*c_exe;

	if (!cmd->cmd || cmd->cmd[0] == '\0')
	{
		printf("cmd null\n");
		return (127);
	}
	if (is_directory(cmd->cmd))
	{
		printf("is directory\n");
		return (127);
	}
	c_exe = get_cmd(data->envar, cmd);
	if (!c_exe)
	{
		printf("path not found [%s]\n", cmd->cmd);
		return (127);
	}
	if (execve(c_exe, cmd->cmdarg, data->env) == -1)
	{
		perror(cmd->cmdarg[0]);
	}
	return (1);
}

int	execute_path_cmd(t_data *data, t_cmd *cmd)
{
	int	res;

	res = check_command(cmd);
	if (res != 0)
		return (res);
	if (execve(cmd->cmd, cmd->cmdarg, data->env) == -1)
		perror(cmd->cmdarg[0]);
	return (1);
}

int	execute_cmd(t_data *data, t_cmd *cmd)
{
	int	res;

	if (!cmd && !cmd->cmd)
		return (1);
	if (!ft_check_iofiles(cmd->iofiles))
		exitshell(data, 1);
	dup_pipe_fds(data->cmds, cmd);
	set_iofds(cmd->iofiles);
	close_iofds(data->cmds, 0);
	if (!ft_strchr(cmd->cmd, '/'))
	{
		if (is_builtin(cmd->cmd))
			res = execute_builtin(data, cmd);
		else
		{
			res = 127;
			res = execute_nopath_cmd(data, cmd);
		}
		if (res != 127)
			exitshell(data, res);
	}
	else
		res = execute_path_cmd(data, cmd);
	exitshell(data, res);
	return (res);
}

int	create_forks(t_data *data)
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
			execute_cmd(data, cmds);
		cmds = cmds->next;
	}
	a = (fork_wait(data));
	return (a);
}

int	ft_execute(t_data *data)
{
	int	res;

	res = check_prepare_exec(data);
	if (res != 127)
		return (res);
	if (!data->cmds->pipeout && !data->cmds->prev
		&& ft_check_iofiles(data->cmds->iofiles))
	{
		set_iofds(data->cmds->iofiles);
		if (is_builtin(data->cmds->cmd))
			res = execute_builtin(data, data->cmds);
		reset_stdio(data->cmds->iofiles);
	}
	if (res != 127)
		return (res);
	return (create_forks(data));
}
