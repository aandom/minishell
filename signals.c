/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandom <aandom@student.abudhabi42.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 08:11:28 by aandom            #+#    #+#             */
/*   Updated: 2023/07/25 08:11:28 by aandom           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	event(void)
{
	return (EXIT_SUCCESS);
}

void	child_signal_handler(int num)
{
	if (num == SIGINT)
		write(1, "\n", 1);
	else if (num == SIGQUIT)
		ft_putstr_fd("Quit: 3\n", 2);
}


void	child_signals( void)
{
	signal(SIGINT, child_signal_handler);
	signal(SIGQUIT, child_signal_handler);
}

void	sigquit_handler(int sig)
{
	(void) sig;
	signal(SIGQUIT, SIG_IGN);
}

void	sigint_handler(int sig)
{
	(void) sig;
	if (g_exit_code == IN_CMD)
	{
		g_exit_code = CTRL_C;
		rl_replace_line("", 0);
		rl_redisplay();
		rl_done = 1;
		return ;
	}
	else if (g_exit_code == IN_HEREDOC)
	{
		g_exit_code = STOP_HEREDOC;
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		rl_done = 1;
		return ;
	}
}

int	init_signals()
{
	rl_catch_signals = 0;
	rl_event_hook = event;
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigquit_handler);
	return (g_exit_code);
}
