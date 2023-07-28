/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandom <aandom@student.abudhabi42.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 19:31:20 by tpetros           #+#    #+#             */
/*   Updated: 2023/07/26 09:16:25 by aandom           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *str)
{
	if (ft_strncmp(str, "cd", 2) == 0)
		return (1);
	else if (ft_strncmp(str, "echo", 4) == 0)
		return (1);
	else if (ft_strncmp(str, "pwd", 3) == 0)
		return (1);
	else if (ft_strncmp(str, "export", 6) == 0)
		return (1);	
	else if (ft_strncmp(str, "unset", 5) == 0)
		return (1);
	else if (ft_strncmp(str, "env", 3) == 0)
		return (1);
	else if (ft_strncmp(str, "exit", 4) == 0)
		return (1);
	else
		return (0);
}

void	execute_builtin(t_data *data, t_cmd *cmd)
{
	if (ft_strncmp(cmd->cmd, "echo", 4) == 0)
		ft_echo(cmd);
	else if (ft_strncmp(cmd->cmd, "cd", 2) == 0)
		ft_cd(data->envar, cmd);
	else if (ft_strncmp(cmd->cmd, "pwd", 3) == 0)
		ft_pwd(data->envar);
	else if (ft_strncmp(cmd->cmd, "export", 6) == 0)
		ft_export(data);	
	else if (ft_strncmp(cmd->cmd, "unset", 5) == 0)
		ft_unset(data, cmd);
	else if (ft_strncmp(cmd->cmd, "env", 3) == 0)
		ft_env(data->envar);
	// else if (ft_strncmp(cmd->cmd, "exit", ft_strlen(cmd->cmd)))
	// 	ft_exit();
}
