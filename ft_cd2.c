/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpetros <tpetros@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 13:54:42 by tpetros           #+#    #+#             */
/*   Updated: 2023/08/08 22:23:03 by tpetros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_wds_env(t_data *data, char *wd)
{
	update_pwd(data, "OLDPWD", get_varvalue(data->envar, "PWD"));
	update_pwd(data, "PWD", wd);
	if (data->oldpwd)
	{
		voidfree(data->oldpwd);
		data->oldpwd = ft_strdup(data->pwd);
	}
	if (data->pwd)
	{
		voidfree(data->pwd);
		data->pwd = ft_strdup(wd);
	}
	voidfree(wd);
	pwd(data->envar, "PWD");
	env_pointer(data);
}

int	ch_dir(t_data *data, char *path)
{
	char	*ret;
	char	*tmp;
	char	cwd[MAX_PATH];

	ret = NULL;
	if (chdir(path) != 0)
		return (print_errmsg("cd", path, "no such file or directory", 2));
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
	return (1);
}


int	ft_cd_new(t_data *d, t_cmd *cmd)
{
	char	*path;


	if (!cmd->cmdarg || !cmd->cmdarg[1] || ft_isspace(cmd->cmdarg[1][0])
		|| cmd->cmdarg[1][0] == '\0' || ft_strcmp(cmd->cmdarg[1], "--") == 0)
	{
		path = get_varvalue(d->envar, "HOME");
		if (!path || *path == '\0' || ft_isspace(*path))
			return (print_errmsg("cd", NULL, "HOME not set", EXIT_FAILURE));
		return (!ch_dir(d, path));
	}
	if (cmd->cmdarg[2] != NULL)
		return (ft_putendl_fd("minishell: cd: too many arguments", 2), 1);
	if (!ft_strcmp(cmd->cmdarg[1], "-"))
	{
		path = get_varvalue(d->envar, "OLDPWD");
		if (!path)
			return (print_errmsg("cd", NULL, "OLDPWD not set", EXIT_FAILURE));
		ft_putendl_fd(path, STDOUT_FILENO);
		return (!ch_dir(d, path));
	}
	return (!ch_dir(d, cmd->cmdarg[1]));
}