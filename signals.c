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

static void	new_prompt(int signal)
{
	if (signal == SIGINT)
	{
		ft_putendl_fd("", STDOUT_FILENO);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_exit_code = 100;
	}
}

void	expecting_input(void)
{
	struct sigaction	sigint_act;
	struct sigaction	sigquit_act;

	ft_bzero(&sigint_act, sizeof(sigint_act));
	sigint_act.sa_handler = &new_prompt;
	sigaction(SIGINT, &sigint_act, NULL);
	ft_bzero(&sigquit_act, sizeof(sigquit_act));
	sigquit_act.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sigquit_act, NULL);
}

static void	print_line(int signal)
{
	if (signal == SIGQUIT && g_exit_code != 50)
	{
		printf("Quit: 3\n");
		rl_on_new_line();
	}
	else if (signal == SIGINT)
	{
		rl_on_new_line();
		g_exit_code = 100;
	}
}

void	not_expecting_input(void)
{
	struct sigaction	act;

	ft_bzero(&act, sizeof(act));
	act.sa_handler = &print_line;
	sigaction(SIGINT, &act, NULL);
	sigaction(SIGQUIT, &act, NULL);
}
