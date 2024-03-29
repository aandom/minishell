/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandom <aandom@student.abudhabi42.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 03:12:53 by aandom            #+#    #+#             */
/*   Updated: 2023/07/29 03:12:53 by aandom           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtin.h"

static int	get_exit_code(char *exarg, int *is_valid, t_exno *ex_no)
{
	unsigned long long	i;

	if (!exarg)
		return (ex_no->exno);
	i = 0;
	while (ft_isspace(exarg[i]))
		i++;
	if (exarg[i] == '\0')
		*is_valid = 0;
	if (exarg[i] == '-' || exarg[i] == '+')
		i++;
	if (!ft_isdigit(exarg[i]))
		*is_valid = 0;
	while (exarg[i])
	{
		if (!ft_isdigit(exarg[i]) && !ft_isspace(exarg[i]))
			*is_valid = 0;
		i++;
	}
	i = ft_atoi_lu(exarg, is_valid);
	return (i % 256);
}

static int	exit_with_arg(t_data *data)
{
	t_cmd	*cmd;

	cmd = data->cmds;
	if (!cmd)
		return (0);
	if (cmd->prev != NULL || cmd->next != NULL)
		return (1);
	return (0);
}

int	ft_exit(t_data *data, char **args, t_exno *ex_no)
{
	int	ex_code;
	int	valid_arg;
	int	is_valid_code;

	valid_arg = exit_with_arg(data);
	is_valid_code = 1;
	if (!valid_arg)
	{
		ft_putendl_fd("exit", STDERR_FILENO);
	}
	if (!args || !args[1])
		ex_code = ex_no->exno;
	else
	{
		ex_code = get_exit_code(args[1], &is_valid_code, ex_no);
		if (!is_valid_code)
			ex_code = errmsg("exit", args[1], INVARG, 2);
		else if (args[2])
			return (errmsg("exit", NULL, "too many arguments", 1));
	}
	exitshell(data, ex_code);
	return (2);
}
