/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpetros <tpetros@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 13:54:42 by tpetros           #+#    #+#             */
/*   Updated: 2023/08/08 21:11:16 by tpetros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd(t_evar *env, char *key)
{
	t_evar	*tmp;
	char	oldpwd[PATH_MAX];
	char	*holder;

	tmp = env;
	if (getcwd(oldpwd, PATH_MAX) == NULL)
		return ;
	while (tmp)
	{
		if (tmp->key && ft_strcmp(key, tmp->key) == 0)
		{
			ft_del_env(&env, key);
			holder = ft_strjoin(ft_strjoin(ft_strdup(key), "="), oldpwd);
			add_back_env(&env, new_evar(holder));
			free(holder);
			break ;
		}
		tmp = tmp->next;
	}
}

t_evar	*find_evar(t_evar *env, char *key)
{
	t_evar	*tmp;

	tmp = env;
	while (tmp != NULL)
	{
		if (tmp->key && strcmp(tmp->key, key) == 0)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

void	update_pwd(t_data *data, char *key, char *value)
{
	char	*new_env;
	t_evar	*old;

	if (key == NULL || value == NULL)
		return ;
	new_env = ft_strjoin(ft_strjoin(key, "="), value);
	old = find_evar(data->envar, key);
	if (old->value != NULL || old->key != NULL)
	{
		free(old->value);
		old->value = ft_strdup(value);
	}
	else
		add_back_env(&data->envar, new_evar(new_env));
	free(new_env);
}

void	ft_previous_dir(t_data *data)
{
	t_evar	*pwd;
	t_evar	*oldpwd;
	char	*new_pwd;
	char	*new_oldpwd;

	pwd = find_evar(data->envar, "PWD");
	oldpwd = find_evar(data->envar, "OLDPWD");
	if (!pwd || !oldpwd || !pwd->value || !oldpwd->value)
		return ;
	new_pwd = ft_strdup(oldpwd->value);
	new_oldpwd = ft_strdup(pwd->value);
	update_pwd(data, "PWD", new_pwd);
	update_pwd(data, "OLDPWD", new_oldpwd);
	if (chdir(new_pwd) == -1)
	{
		free(new_pwd);
		free(new_oldpwd);
		return ;
	}
	free(new_pwd);
	free(new_oldpwd);
	env_pointer(data);
}

void	ft_expanding_tilda(t_data *data)
{
	t_evar	*tmp;
	char	*h;
	char	*temp;

	tmp = data->envar;
	h = NULL;
	while (tmp)
	{
		if (tmp->key && ft_strcmp("HOME", tmp->key) == 0)
		{
			temp = ft_strtrim(data->cmds->cmdarg[1], "~");
			h = ft_strjoin(ft_strdup(tmp->value), temp);
		}
		tmp = tmp->next;
	}
	if (h)
	{
		if (chdir(h) != 0)
			perror("minishell: cd");
	}
	free(h);
	free(temp);
}

void	ft_home(t_data *data)
{
	t_evar	*tmp;

	tmp = data->envar;
	while (tmp)
	{
		if (tmp->key && ft_strcmp("HOME", tmp->key) == 0)
			if (chdir(tmp->value) != 0)
				perror("minishell: cd");
		tmp = tmp->next;
	}
}

int	ft_cd(t_data *d, t_cmd *cmd)
{
	int		code;

	code = EXIT_SUCCESS;
	if (!cmd || !cmd->cmdarg || cmd->cmdarg[2] != NULL)
		return (ft_putendl_fd("minishell: cd: too many arguments", 2), 1);
	if (!ft_strcmp(cmd->cmdarg[1], "-"))
	{
		ft_previous_dir(d);
		return (EXIT_SUCCESS);
	}
	pwd(d->envar, "OLDPWD");
	if (cmd->cmdarg[1] && cmd->cmdarg[1][0] == '~' && cmd->cmdarg[1][1]
		!= '\0' && ft_strcmp(cmd->cmdarg[1], ".."))
		ft_expanding_tilda(d);
	else if ((cmd->cmdarg[1]) == NULL || !ft_strncmp(cmd->cmdarg[1], "~", 1))
		ft_home(d);
	else if (chdir(cmd->cmdarg[1]) != 0)
	{
		perror("minishell: cd");
		return (code = EXIT_FAILURE);
	}
	pwd(d->envar, "PWD");
	env_pointer(d);
	return (code);
}
