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


int ft_check_iofiles(t_iofiles *iofds)
{
    if (!iofds || (!iofds->infile && !iofds->outfile))
        return (1);
    if ((iofds->infile && iofds->fdin == -1) || (iofds->outfile && iofds->fdout == -1))
        return (0);
    return (1);
}


int create_pipes(t_data *data)
{
    int     *tube;
    t_cmd   *cmds;

    cmds = data->cmds;
    while(cmds)
    {
        if (cmds->pipeout || (cmds->prev && cmds->prev->pipeout))
        {
            tube = malloc(sizeof(int) * 2);
            if (!tube || pipe(tube) != 0)
                return (0);
            cmds->tube = tube;
        }
        cmds = cmds->next;
    }
    return(1);
}

static  int check_prepare_exec(t_data *data)
{
    if (!data || !data->cmds)
        return(EXIT_SUCCESS);
    if (!data->cmds->cmd)
    {
        if (data->cmds->iofiles && !ft_check_iofiles(data->cmds->iofiles))
            return (EXIT_FAILURE);
        return (EXIT_SUCCESS);
    }
    
    if (!create_pipes(data))
        return(EXIT_FAILURE);
    return (127);

}

void    close_unused_pipes(t_cmd *headcmd, t_cmd *curcmd)
{
    while (headcmd)
    {
        if (headcmd != curcmd && headcmd->tube)
        {
            // printf("closing for [%s] cur cmd [%s]\n", headcmd->cmd, curcmd->cmd);
            close(headcmd->tube[0]);
            close(headcmd->tube[1]);
        }
        headcmd = headcmd->next;
    }
}

void    reset_stdio(t_iofiles *iofds)
{
    if (!iofds)
        return ;
    if (iofds->stdin_cp != -1)
    {
        dup2(iofds->stdin_cp, STDIN_FILENO);
        close(iofds->stdin_cp);
        iofds->stdin_cp = -1;
    }
    if (iofds->stdout_cp != -1)
    {
        dup2(iofds->stdout_cp, STDOUT_FILENO);
        close(iofds->stdout_cp);
        iofds->stdout_cp = -1;
    }
    return ;
}

void    close_iofds(t_cmd *cmds, int code)
{
    if (cmds->iofiles)
    {
        if (cmds->iofiles->fdin != -1)
            close(cmds->iofiles->fdin);
        if (cmds->iofiles->fdout != -1)
            close (cmds->iofiles->fdout);
        if (code = 1)
            reset_stdio(cmds->iofiles);
    }
    close_unused_pipes(cmds, NULL);
}

void    dup_pipe_fds(t_cmd  *headcmd, t_cmd *curcmd)
{
    if(!curcmd)
        return ;
    if (curcmd->prev && curcmd->prev->pipeout)
        dup2(curcmd->prev->tube[0], STDIN_FILENO);
    if (curcmd->pipeout)
        dup2(curcmd->tube[1], STDOUT_FILENO);
    close_unused_pipes(headcmd, curcmd);
    return ;
}

void    set_iofds(t_iofiles *iofds)
{
    if (!iofds)
    {
        // printf("no iofds\n");
        return ;
    }
    iofds->stdin_cp = dup(STDIN_FILENO);
    if (iofds->stdin_cp == -1)
    {
        printf("here5\n");
        return ;
    }
    iofds->stdout_cp = dup(STDOUT_FILENO);
    if (iofds->stdout_cp == -1)
        return ;
    if (iofds->fdin != -1)
        dup2(iofds->fdin, STDIN_FILENO);
    if (iofds->fdout != -1)
        dup2(iofds->fdout, STDOUT_FILENO);
    return ;
}

char    **get_splited_path(t_evar *evar)
{
    while (evar)
    {
        if (!ft_strncmp(evar->key, "PATH", 4))
            return (ft_split(evar->value, ':'));
        evar = evar->next;
    }
    return (NULL);
}

char    *get_cmd(t_evar *envar, t_cmd *cmd)
{

	char	*c;
    char    **path;
	char	*tmp;
	int		i;

	if (!envar)
		return (ft_strdup(cmd->cmd));
    path = get_splited_path(envar);
    i = 0;
	while (path && path[i])
	{
		tmp = ft_strjoin(path[i], "/");
		c = ft_strjoin(tmp, cmd->cmd);
		free(tmp);
		if (access(c, F_OK | X_OK) == 0)
			return (c);
		free(c);
		i++;
	}
	return (NULL);
}

int execute_nopath_cmd(t_data *data, t_cmd *cmd)
{
    char    *c_exe;

    if (!cmd)
        exit(printf("empty command\n"));
    c_exe = get_cmd(data->envar, cmd);
    if(!c_exe)
        exit(printf("command not found\n"));
    if (execve(c_exe, cmd->cmdarg, data->env) == -1)
	{
		perror(cmd->cmdarg[0]);
		exit(printf("execve error\n"));
	}
    return(0);
}

int execute_cmd(t_data *data, t_cmd *cmd)
{
    int res;

    if (!cmd && !cmd->cmd)
        return (0);
    
    if (!ft_check_iofiles(cmd->iofiles))
        return (0);
    dup_pipe_fds(data->cmds, cmd);
    set_iofds(data->cmds->iofiles);
    if (!ft_strchr(cmd->cmd, '/'))
    {
        // if (is_builtin(cmd->cmd))
        //     res = execute_builtin(data, cmd);

            // printf("fd2= %d, for %s\n", cmd->iofiles->fdout, cmd->iofiles->outfile);
        // else
            res = execute_nopath_cmd(data, cmd);
    }
    // else
    //     res = execute_path_cmd(data, cmd);
    if (res == 0)
        exit(printf("command executed successfully"));
}

int fork_wait(t_data *data)
{
    pid_t	wstatus;
	int		status;
	int		res;

	close_iofds(data->cmds, 0);
	res = 0;
	wstatus = 0;
	while (wstatus != -1 || errno != ECHILD)
	{
		wstatus = waitpid(-1, &status, 0);
		if (wstatus == data->pid)
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

int create_forks(t_data *data)
{
    t_cmd   *cmds;
    
    cmds = data->cmds;
    while (cmds)
    {

        data->pid = fork();
        if (data->pid == -1)
            return (0);
        else if (data->pid == 0)
        {
            // printf("cmd - %s\n ", cmds->cmd);
            execute_cmd(data, cmds);
        }
        cmds = cmds->next;
    }
    return (fork_wait(data));
    // waitpid(-1, NULL, 0);
}


int ft_execute(t_data *data)
{
    int res;

    res = check_prepare_exec(data);
    if (res != 127)
        return (res);
    res = create_forks(data);
    t_cmd *tmp = data->cmds;

    // while (tmp->cmd)
    // {
	// 	waitpid(-1, NULL, 0);
    //     tmp = tmp->next;
    // }
}