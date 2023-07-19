/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpetros <tpetros@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 20:27:33 by tpetros           #+#    #+#             */
/*   Updated: 2023/07/15 20:27:34 by tpetros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	all_n(char *str)
{
	int	i;

	i = 1;
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

void	ft_echo(t_cmd *cmd)
{
	int	n_flag;
	int	i;

	i = 1;
	while (cmd->cmdarg[i] && (!ft_strncmp(cmd->cmdarg[i], "-n", 2) && all_n(cmd->cmdarg[i])))
	{
		n_flag = 1;
		i++;
	}
	while (cmd->cmdarg[i])
	{
		write(1, cmd->cmdarg[i], ft_strlen(cmd->cmdarg[i]) + 1);
		if (cmd->cmdarg[i + 1] && cmd->cmdarg[i][0] != '\0')
			write(1, " ", 1);
		i++;
	}
	if (n_flag != 1)
		write(1, '\n', 1);
}




// #include <unistd.h>
// size_t	ft_strlen(const char *s);
// int	ft_strncmp(const char *s1, const char *s2, size_t n);

// int	all_n(char *str)
// {
// 	int	i;

// 	i = 1;
// 	while (str[i])
// 	{
// 		if (str[i] != 'n')
// 			return (0);
// 		i++;
// 	}
// 	return (1);
// }

// void	ft_echo(char **cmd)
// {
// 	int	n_flag;
// 	int	i;

// 	i = 1;
// 	while (cmd[i] && (!ft_strncmp(cmd[i], "-n", 2) && all_n(cmd[i])))
// 	{
// 		n_flag = 1;
// 		i++;
// 	}
// 	while (cmd[i])
// 	{
// 		write(1, cmd[i], ft_strlen(cmd[i]) + 1);
// 		if (cmd[i + 1] && cmd[i][0] != '\0')
// 			write(1, " ", 1);
// 		i++;
// 	}
// 	if (n_flag != 1)
// 		write(1, "\n", 1);
// }

// int main(int ac, char **av)
// {
// 	ft_echo(av);
// }