/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpetros <tpetros@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 13:54:42 by tpetros           #+#    #+#             */
/*   Updated: 2023/07/28 13:54:44 by tpetros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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
			ft_memset(tmp->value, 0, ft_strlen(tmp->value));
			ft_strlcpy(tmp->value, oldpwd, ft_strlen(tmp->value));
		}
		tmp = tmp->next;
	}
}

void	new_pwd(t_evar *env)
{
	t_evar	*tmp;
	char 	newpwd[PATH_MAX];

	tmp = env;
	getcwd(newpwd, PATH_MAX);
	while (tmp)
	{
		if (ft_strncmp("PWD", tmp->key, 3) == 0)
		{
			ft_memset(tmp->value, 0, ft_strlen(tmp->value));
			ft_strlcpy(tmp->value, newpwd, ft_strlen(tmp->value));
		}
		tmp = tmp->next;
	}
}

void	ft_cd(t_evar *env, t_cmd *cmd)
{
	t_evar	*tmp;

	tmp = env;
	old_pwd(env);
	if (cmd->cmdarg[1] == NULL || ft_strncmp(cmd->cmdarg[1], "~", 1) = 0)
	{
		while (tmp)
		{
			if (ft_strncmp("HOME", tmp->key, 4) = 0)
			{
				ft_memset(tmp->value, 0, ft_strlen(tmp->value));
				chdir(tmp->value);
				break ;
			}
			tmp = tmp->next;
		}
	}
	else if (chdir(cmd->cmdarg[1]) != 0)
		printf("%s: no such file or directory\n", str[1]);
	new_pwd(env);
}
