/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandom <aandom@student.abudhabi42.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 14:11:56 by aandom            #+#    #+#             */
/*   Updated: 2023/07/01 15:52:04 by aandom           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_exit_code;

void	ft_minishell_new(t_data *data, t_exno *ex_s)
{
	while (1)
	{
		init_signals();
		data->input = readline(PROMPT);
		set_signals_noninteractive();
		if (g_exit_code == CTRL_C)
		{
			ex_s->exno = g_exit_code;
			g_exit_code = IN_MINI;
		}
		if (data->input != NULL && all_space(data->input))
			ex_s->exno = ex_s->exno;
		else if (parse_input(data, ex_s) == 1)
			ex_s->exno = ft_execute(data, ex_s);
		else if (ex_s->exno != CTRL_C && g_exit_code != IN_CMD)
			ex_s->exno = 1;
		free_all(data, 0);
	}
}

int	initialize_data(t_data *data, char **env)
{
	if (!initialize_envar(data, env))
	{
		ft_putendl_fd("Couldn't initialize env", STDERR_FILENO);
		return (0);
	}
	if (!init_wds(data))
	{
		ft_putendl_fd("Couldn't initialize working directory", STDERR_FILENO);
		return (0);
	}
	data->lexed = NULL;
	data->cmds = NULL;
	g_exit_code = IN_MINI;
	data->pid = -1;
	data->input = NULL;
	copy_env(data, env);
	return (1);
}

void	my_minishell(char **env)
{
	t_data	*data;
	t_exno	ex_s;

	ex_s.exno = 0;
	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		return ;
	ft_memset(data, 0, sizeof(t_data));
	if (!initialize_data(data, env))
		exitshell(NULL, EXIT_FAILURE);
	ft_shlvl(data, data->envar);
	ft_minishell_new(data, &ex_s);
	exitshell(data, ex_s.exno);
	return ;
}

int	main(int ac, char **av, char **env)
{
	(void) av;
	if (ac != 1)
		return (127);
	my_minishell(env);
}
