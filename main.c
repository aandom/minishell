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

#include "minishell.h"

void	sig_ctrlc(int sig)
{
	if (sig == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	ft_arr_freer(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	ft_free_iofile(t_iofiles *iofiles)
{
	if (!iofiles)
		return ;
	if (iofiles->infile)
		free(iofiles->infile);
	if (iofiles->outfile)
		free(iofiles->outfile);
	if (iofiles->here_delimter)
		free(iofiles->here_delimter);
	free(iofiles);
}

void	ft_lex_freer(t_lexer *lex)
{
	t_lexer *tmp;

	tmp = lex;
	while (tmp)
	{
		free(tmp->str);
		tmp = tmp->next;
	}
	free(lex);
}

void    ft_cmd_freer(t_cmd *cmd)
{
	t_cmd	*tmp;

	tmp = cmd;
	while (tmp)
	{
		free(tmp->cmd);
		// free(tmp->path);
		ft_free_iofile(tmp->iofiles);
		ft_arr_freer(tmp->cmdarg);
		tmp = tmp->next;
	}
	free(cmd);
}



void    ft_minishell(char **env)
{
    t_data  *data;
    int     ex_code;
    
    data = malloc(sizeof(t_data));
    copy_env(data, env);
    while (1)
    {
		signal(SIGINT, sig_ctrlc);
		signal(SIGQUIT, SIG_IGN);
		data->input = readline(PROMPT);
		ft_parser(data);
		remove_quotes(&data->lexed);
		ft_expand(data);
		extract_command(data, data->lexed);
		ex_code = ft_execute(data);
		free(data->input);
		ft_cmd_freer(data->cmds);
		ft_lex_freer(data->lexed);
    }
}


int main(int ac, char **av, char **env)
{
    (void) av;
    (void) env;
    if (ac != 1)
	return (0);
    // printf("\033[34m"); // Set color to blue
    // printf("⠀⢀⣀⣀⣀⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
    // printf("⢀⣧⠞⠁⠀⢀⡹⠆⠠⠤⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
    // printf("⠀⡇⠀⢀⡴⠋⠀⠀⠀⠀⣨⠖⠀⠠⠤⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
    // printf("⠀⡇⢠⠎⠀⠀⠀⢀⡴⠛⠁⠀⠀⠀⠀⠀⠙⣦⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
    // printf("⠀⠸⣶⣾⣦⣄⡴⠋⠀⠀⠀⠀⠀⠀⠀⠀⠀⠘⣧⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
    // printf("⠀⢸⡿⣭⣿⡟⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢹⣷⣶⣶⣦⡤⡀⠀⠀⠀⠀\n");
    // printf("⠀⠈⢿⣿⣽⢿⡄⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡜⢸⣿⣿⣿⣿⣯⡲⡄⠀⠀\n");
    // printf("⠀⠀⠈⢻⣿⣿⢿⣖⡄⣀⠀⠀⠀⠀⠀⠀⠀⡴⠁⣾⣿⣿⠿⠿⠇⠘⡆⠀\n");
    // printf("⠀⠀⠀⢸⣿⣿⣿⣿⣾⣿⣿⣦⣄⡀⠀⢀⠞⠀⣼⣿⣿⠟⠁⠀⠀⠀⠀⢸⠀\n");
    // printf("⠀⠀⠀⠈⣿⣿⣿⣿⣿⣿⣿⣿⣿⡆⡜⡌⢰⣿⣟⠇⠀⠄⠀⠀⠀⠀⢸⡇\n");
    // printf("⠀⠀⠀⠀⠹⣿⣷⣿⣻⣿⣿⣿⣿⣧⣧⠃⢾⡿⠙⠘⠘⠀⠀⠀⠀⠀⢸⡇\n");
    // printf("⠀⠀⠀⠀⠀⠈⢿⣿⣿⣿⣿⣟⣛⠀⣽⣷⡀⢳⡀⠀⠀⠀⠀⠀⠀⢀⡎⠀\n");
    // printf("⠀⠀⠀⠀⠀⠀⠀⠀⠈⠛⠿⣿⣿⣿⣿⣿⣿⣦⣍⠒⠂⠀⠀⠀⣠⠎⠀⠀\n");
    // printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠉⠉⠉⠉⠉⠉⠙⠛⠒⠒⠋⠁⠀⠀⠀\n");
    // printf("\033[0m"); // Reset color to default

    ft_minishell(env);
}