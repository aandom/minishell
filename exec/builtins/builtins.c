/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandom <aandom@student.abudhabi42.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 19:31:20 by tpetros           #+#    #+#             */
/*   Updated: 2023/07/30 17:17:20 by aandom           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_builtin(char *str)
{
	if (ft_strncmp(str, "echo", ft_strlen(str)))
		return (1);
	else if (ft_strncmp(str, "cd", ft_strlen(str)))
		return (1);
	else if (ft_strncmp(str, "pwd", ft_strlen(str)))
		return (1);
	else if (ft_strncmp(str, "export", ft_strlen(str)))
		return (1);	
	else if (ft_strncmp(str, "unset", ft_strlen(str)))
		return (1);
	else if (ft_strncmp(str, "env", ft_strlen(str)))
		return (1);
	else if (ft_strncmp(str, "exit", ft_strlen(str)))
		return (1);
	else
		return (0);
}

void	exec_builtin(t_cmd *cmd)
{
	if (ft_strncmp(cmd->cmd, "echo", ft_strlen(cmd->cmd)))
		ft_echo(cmd);
	else if (ft_strncmp(cmd->cmd, "cd", ft_strlen(cmd->cmd)))
		ft_cd();
	else if (ft_strncmp(cmd->cmd, "pwd", ft_strlen(cmd->cmd)))
		ft_pwd();
	else if (ft_strncmp(cmd->cmd, "export", ft_strlen(cmd->cmd)))
		ft_export();	
	else if (ft_strncmp(cmd->cmd, "unset", ft_strlen(cmd->cmd)))
		ft_unset();
	else if (ft_strncmp(cmd->cmd, "env", ft_strlen(cmd->cmd)))
		ft_env();
	else if (ft_strncmp(cmd->cmd, "exit", ft_strlen(cmd->cmd)))
		ft_exit();
}
