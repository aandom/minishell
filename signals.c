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

void	sigquit_handler(int sig)
{
	(void) sig;
	if (g_exit_code == IN_CMD)
	{
		g_exit_code = CTRL_BS;
		rl_replace_line("", 0);
		rl_redisplay();
		rl_done = 1;
		ft_putendl_fd("Quit: ", STDERR_FILENO);
		return ;
	}
}

void	sigint_handler(int sig)
{
	(void) sig;
	if (g_exit_code != IN_HEREDOC)
		ft_putstr_fd("\n", STDERR_FILENO);
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
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

int	init_signals(t_exno *ex_s)
{
	rl_catch_signals = 0;
	rl_event_hook = event;
	if (signal(SIGINT, sigint_handler) == SIG_ERR)
	{
		printf("sigint\n");
		ex_s->exno = 130;
	}
	if (signal(SIGQUIT, sigquit_handler) == SIG_ERR)
	{
		printf("siquit\n");
		ex_s->exno = 1;
	}
	return (g_exit_code);
}
