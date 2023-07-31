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

#include "minishell.h"

int check_max(unsigned long long num, int sign, int *is_valid)
{
    if (sign == 1 && num > LONG_MAX)
        *is_valid = 1;
    else if (sign == -1 && num > -(unsigned long)LONG_MIN)
		*is_valid = 1;
	return (*is_valid);
}

int	set_sign(const char *str, int *sign, int i)
{
	int	c;

	c = 0;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			*sign = *sign * -1;
		c++;
	}
	return (c);
}

long long  ft_atoi_lu(char *str, int *is_valid)
{
    unsigned long long  num;
    size_t  i;
    int     sign;

    i = 0;
    sign = 1;
    num = 0;
    while (str[i] && ft_isspace(str[i]))
        i++;
    i = i + set_sign(str, &sign, i);
    while (str[i] && ft_isdigit(str[i]))
    {
        num = (num * 10) + (str[i] - '0');
		if (check_max(num, sign, is_valid))
			break;
		i++;
    }
    return (num * sign);
}

int get_exit_code(char *exarg, int *is_valid)
{
    unsigned long long   i;

    if (!exarg)
        return(exit_code);
    i = 0;
    while (ft_isspace(exarg[i]))
        i++;
    if(exarg[i] == '\0')
        *is_valid = 0;
    if(exarg[i] == '-' || exarg[i] == '+')
        i++;
    if(!ft_isdigit(exarg[i]))
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


int exit_with_arg(t_data *data)
{
    t_cmd   *cmd;

    cmd = data->cmds;
    if (!cmd)
        return (0);
    if (cmd->prev || cmd->next)
        return (1);
    return (0);
}

int ft_exit(t_data *data, char **args)
{
    int ex_code;
    int valid_arg;
    int is_valid_code;

    valid_arg = exit_with_arg(data);
    is_valid_code = 1; 
    if (!valid_arg)
        printf("exit\n");
    if (!args || !args[1])
        ex_code = exit_code;
    else
    {
        ex_code = get_exit_code(args[1], &is_valid_code);
        if(!is_valid_code)
        {
            printf("exit: %s: numeric argument required\n", args[1]);
            exit_code = 2;
        }
        else if (args[2])
            return (printf("exit: too many arguments\n"), 1);
    }
    exitshell(data, exit_code);
    return (2);
}