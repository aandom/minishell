/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpetros <tpetros@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 19:31:20 by tpetros           #+#    #+#             */
/*   Updated: 2023/08/02 12:48:38 by tpetros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *str)
{
	if (!ft_strcmp(str, "cd"))
		return (1);
	else if (!ft_strcmp(str, "echo"))
		return (1);
	else if (!ft_strcmp(str, "pwd"))
		return (1);
	else if (!ft_strcmp(str, "export"))
		return (1);
	else if (!ft_strcmp(str, "unset"))
		return (1);
	else if (!ft_strcmp(str, "env"))
		return (1);
	else if (!ft_strcmp(str, "exit"))
		return (1);
	else
		return (0);
}

int	execute_builtin(t_data *data, t_cmd *cmd)
{
	int	code;

	code = 0;
	if (!ft_strcmp(cmd->cmd, "echo"))
		code = ft_echo(cmd);
	else if (!ft_strcmp(cmd->cmd, "cd"))
		code = ft_cd(data->envar, cmd);
	else if (!ft_strcmp(cmd->cmd, "pwd"))
		code = ft_pwd();
	else if (!ft_strcmp(cmd->cmd, "export"))
		code = ft_export(data);
	else if (!ft_strcmp(cmd->cmd, "unset"))
		code = ft_unset(data, cmd);
	else if (!ft_strcmp(cmd->cmd, "env"))
		ft_env(data->envar);
	else if (!ft_strcmp(cmd->cmd, "exit"))
		code = ft_exit(data, cmd->cmdarg);
	return (code);
}
