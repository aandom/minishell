/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandom <aandom@student.abudhabi42.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 20:51:46 by aandom            #+#    #+#             */
/*   Updated: 2023/08/07 20:51:46 by aandom           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

int	check_prepare_exec(t_data *data)
{
	if (!data || !data->cmds)
		return (EXIT_SUCCESS);
	if (!data->cmds->cmd)
	{
		if (data->cmds->iofiles && !ft_check_iofiles(data->cmds->iofiles))
			return (EXIT_FAILURE);
		return (EXIT_SUCCESS);
	}
	if (!create_pipes(data))
		return (EXIT_FAILURE);
	return (127);
}

static char	**get_splited_path(t_evar *evar)
{
	while (evar)
	{
		if (!ft_strcmp(evar->key, "PATH"))
			return (ft_split(evar->value, ':'));
		evar = evar->next;
	}
	return (NULL);
}

char	*get_cmd(t_evar *envar, t_cmd *cmd)
{
	char	*c;
	char	**path;
	int		i;
	t_evar	*tmp;

	tmp = find_evar(envar, "PATH");
	if (!tmp)
		return (ft_strdup(cmd->cmd));
	path = get_splited_path(envar);
	i = 0;
	while (path && path[i])
	{
		c = ft_strjoin(ft_strjoin(ft_strdup(path[i]), "/"), cmd->cmd);
		if (access(c, F_OK) == 0)
		{
			ft_arr_freer(path);
			return (c);
		}
		free(c);
		i++;
	}
	errmsg(cmd->cmd, NULL, "command not found", 127);
	ft_arr_freer(path);
	return (NULL);
}

int	is_directory(char *cmd)
{
	struct stat	dirstat;

	ft_memset(&dirstat, 0, sizeof(dirstat));
	stat(cmd, &dirstat);
	return (S_ISDIR(dirstat.st_mode));
}

int	check_command(t_cmd *cmd)
{
	if (access(cmd->cmd, F_OK) != 0)
		return (errmsg(cmd->cmd, NULL, strerror(errno), 127));
	else if (is_directory(cmd->cmd))
		return (errmsg(cmd->cmd, NULL, "Is a directory", 126));
	else if (access(cmd->cmd, F_OK | X_OK) != 0)
		return (errmsg(cmd->cmd, NULL, strerror(errno), 126));
	return (0);
}
