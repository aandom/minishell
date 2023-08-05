/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpetros <tpetros@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 13:54:42 by tpetros           #+#    #+#             */
/*   Updated: 2023/08/06 00:34:42 by tpetros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	old_pwd(t_evar *env)
{
	t_evar	*tmp;
	char	oldpwd[PATH_MAX];

	tmp = env;
	getcwd(oldpwd, PATH_MAX);
	while (tmp)
	{
		if (ft_strncmp("OLDPWD", tmp->key, 6) == 0)
		{
			ft_del_env(&env, "OLDPWD");
			add_back_env(&env, new_evar(ft_strjoin("OLDPWD=", oldpwd)));
			break ;
		}
		tmp = tmp->next;
	}
}

void	new_pwd(t_evar *env)
{
	t_evar	*tmp;
	char	newpwd[PATH_MAX];

	tmp = env;
	getcwd(newpwd, PATH_MAX);
	while (tmp)
	{
		if (ft_strncmp("PWD", tmp->key, 3) == 0)
		{
			ft_del_env(&env, "PWD");
			add_back_env(&env, new_evar(ft_strjoin("PWD=", newpwd)));
			break ;
		}
		tmp = tmp->next;
	}
}

// void	ft_previous_dir(t_data *data)
// {
// 	t_evar	*tmp;
// 	char	*old;
// 	char	*new;

// 	tmp = data->envar;
// 	while (tmp)
// 	{
// 		if (ft_strcmp("PWD", tmp->key) == 0)
// 		{
// 			new = ft_strdup(tmp->value);
// 			ft_del_env(&data->envar, "PWD");
// 		}
// 		tmp = tmp->next;
// 	}
// 	tmp = data->envar;
// 	while (tmp)
// 	{
// 		if (ft_strcmp("OLDPWD", tmp->key) == 0)
// 		{
// 			old = ft_strdup(tmp->value);
// 			ft_del_env(&data->envar, "OLDPWD");
// 		}
// 		tmp = tmp->next;
// 	}
// 	add_back_env(&data->envar, new_evar(ft_strjoin("PWD=", new)));
// 	add_back_env(&data->envar, new_evar(ft_strjoin("OLDPWD=", old)));
	
// 	tmp = data->envar;
// 	while (tmp)
// 	{
// 		if (ft_strcmp("OLDPWD", tmp->key) == 0)
// 			chdir(tmp->value);
// 		tmp = tmp->next;
// 	}
// 	env_pointer(data);
// }

int	ft_cd(t_data *d, t_cmd *cmd)
{
	t_evar	*tmp;
	int		code;

	tmp = d->envar;
	code = EXIT_SUCCESS;
	if (cmd->cmdarg[2] != NULL)
		return (ft_putendl_fd("minishell: cd: too many arguments"
				, STDERR_FILENO), EXIT_FAILURE);
	// if (!ft_strncmp(cmd->cmdarg[1], "-", 1))
	// {
	// 	ft_previous_dir(d);
	// 	return (EXIT_SUCCESS);
	// }
	old_pwd(d->envar);
	if ((cmd->cmdarg[1]) == NULL || !ft_strncmp(cmd->cmdarg[1], "~", 1))
	{
		while (tmp)
		{
			if (ft_strcmp("HOME", tmp->key) == 0)
				chdir(tmp->value);
			tmp = tmp->next;
		}
	}
	else if (chdir(cmd->cmdarg[1]) != 0)
	{
		perror("minishell: cd");
		return (code = EXIT_FAILURE, code);
	}
	new_pwd(d->envar);
	env_pointer(d);
	return (code);
}
