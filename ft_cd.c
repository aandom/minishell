/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpetros <tpetros@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 13:54:42 by tpetros           #+#    #+#             */
/*   Updated: 2023/08/03 17:06:25 by tpetros          ###   ########.fr       */
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

int	ft_cd(t_evar *env, t_cmd *cmd)
{
	t_evar	*tmp;
	int		code;

	tmp = env;
	code = EXIT_SUCCESS;
	if (cmd->cmdarg[2] != NULL)
		return (ft_putendl_fd("minishell: cd: too many arguments", STDERR_FILENO), EXIT_FAILURE);
	old_pwd(env);
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
	new_pwd(env);
	return (code);
}
