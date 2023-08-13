/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandom <aandom@student.abudhabi42.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 13:54:42 by tpetros           #+#    #+#             */
/*   Updated: 2023/08/13 04:50:24 by aandom           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ch_dir(t_data *data, char *path)
{
	char	*ret;
	char	*tmp;
	char	cwd[MAX_PATH];

	ret = NULL;
	if (chdir(path) != 0)
	{
		print_errmsg("cd", path, "no such file or directory", 2);
		return (voidfree(path), 0);
	}
	ret = getcwd(cwd, MAX_PATH);
	if (!ret)
	{
		print_errmsg(CD_ERR, CD_ERR2, strerror(errno), errno);
		ret = ft_strjoin(ft_strdup(data->pwd), "/");
		tmp = ret;
		ret = ft_strjoin(ft_strdup(tmp), path);
		voidfree(tmp);
	}
	else
		ret = ft_strdup(cwd);
	update_wds_env(data, ret);
	voidfree(path);
	return (1);
}

char	*ft_expanding_tilda(t_data *data)
{
	char	*h;
	char	*temp;

	h = get_varvalue(data->envar, "HOME");
	temp = ft_strtrim(data->cmds->cmdarg[1], "~");
	h = ft_strjoin(h, temp);
	free(temp);
	return (h);
}

int	ft_cd_helper(t_data *d, t_cmd *cmd, int *i)
{
	char	*tmp;

	*i = 0;
	if (cmd->cmdarg[1][0] != '~')
		return (1);
	if (cmd->cmdarg[1][1] != '/')
	{
		*i = 1;
		return (print_errmsg("cd", cmd->cmdarg[1], NFE, 1), 0);
	}
	tmp = ft_expanding_tilda(d);
	if (!tmp)
		return (print_errmsg("cd", tmp, "No such file or directory", 1), 0);
	else if (cmd->cmdarg[1] && cmd->cmdarg[1][0] == '~' && cmd->cmdarg[1][1]
		!= '\0' && ft_strcmp(cmd->cmdarg[1], ".."))
	{
		*i = !ch_dir(d, tmp);
		return (0);
	}
	voidfree(tmp);
	return (0);
}

int	is_to_home(t_data *d, t_cmd *cmd)
{
	(void) d;
	if (!cmd->cmdarg || !cmd->cmdarg[1] || ft_isspace(cmd->cmdarg[1][0])
		|| cmd->cmdarg[1][0] == '\0' || ft_strcmp(cmd->cmdarg[1], "--") == 0
		|| ft_strcmp(cmd->cmdarg[1], "~") == 0)
		return (1);
	return (0);
}

int	ft_cd_new(t_data *d, t_cmd *cmd)
{
	char	*path;
	int		i;

	if (arg_counter(cmd->cmdarg) > 2)
		return (ft_putendl_fd("minishell: cd: too many arguments", 2), 1);
	if (is_to_home(d, cmd))
	{
		path = get_varvalue(d->envar, "HOME");
		if (!path || *path == '\0' || ft_isspace(*path))
			return (print_errmsg("cd", NULL, "HOME not set", EXIT_FAILURE));
		return (!ch_dir(d, path));
	}
	else if (!ft_strcmp(cmd->cmdarg[1], "-"))
	{
		path = get_varvalue(d->envar, "OLDPWD");
		if (!path || ft_strcmp(path, "") == 0)
			return (print_errmsg("cd", NULL, "OLDPWD not set", EXIT_FAILURE));
		ft_putendl_fd(path, STDOUT_FILENO);
		return (!ch_dir(d, path));
	}
	else if (!ft_cd_helper(d, cmd, &i))
		return (i);
	path = ft_strdup(cmd->cmdarg[1]);
	return (!ch_dir(d, path));
}
