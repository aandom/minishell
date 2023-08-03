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

int exit_code;

void	ft_arr_freer(char **str)
{
	int	i;

	i = 0;
	while (str && str[i])
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

void    free_all(t_data *data)
{
    if (data && data->input)
        voidfree(data->input);
    if (data && data->lexed)
        ft_lst_clear_token(&data->lexed, voidfree);
    if (data && data->cmds)
        ft_lst_clear_cmd(&data->cmds, voidfree);
    // if (data->env)
    //     ft_arr_freer(data->env);
    // if (data->envar)
}

void    exitshell(t_data *data, int excode)
{
    if (data)
    {
        if (data->cmds && data->cmds->iofiles)
            close_iofds(data->cmds, 1);
        free_all(data);
        if (data->env)
            ft_arr_freer(data->env);
        // if (data->envar)
        voidfree(data);
    }
    exit(excode);
}

int all_space(char *str)
{
    int i;

    i = 0;
    while (str [i])
    {
        if (!ft_isspace(str[i]))
            return (0);
        i++;
    }
    return (1);
}

int parse_input(t_data *data)
{
    if (data->input == NULL)
        ft_exit(data, NULL);
    else if (ft_strcmp(data->input, "\0") == 0)
        return (0);
    else if (all_space(data->input))
        return (1);
    add_history(data->input);
    if (ft_parser(data) == 1)
        return (0);
    if (data->lexed->type == END)
        return (0);
    if (parsing_check(&data->lexed) == 1)
        return (0);
    if (ft_expand_var(data, &data->lexed) == 0)
        return (0);
    remove_quotes(&data->lexed);
    extract_command(data, data->lexed);
    return(1);
}


void	ft_minishell_new(t_data *data)
{
	while ('T')
	{
		expecting_input();
		data->input = readline(PROMPT);
		not_expecting_input();
		if (parse_input(data) == 1)
			exit_code = ft_execute(data);
		else
			exit_code = 1;
		free_all(data);
	}
}

int initialize_data(t_data *data, char **env)
{
    if (!initialize_envar(data, env))
    {
        ft_putendl_fd("Couldn't initialize env", STDERR_FILENO);
        return (0);
    }
    data->lexed = NULL;
    data->cmds = NULL;
    exit_code = 0;
    data->pid = -1;
    data->input = NULL;
    copy_env(data, env);
    return(1);
}


void    my_minishell(char **env)
{
    t_data  *data;
    int     code;
    
    data = malloc(sizeof(t_data));
    ft_memset(data, 0, sizeof(t_data));
	if (!initialize_data(data, env))
		exitshell(NULL, EXIT_FAILURE);
	ft_minishell_new(data);
	exitshell(data, exit_code);
	return ;
} 


int main(int ac, char **av, char **env)
{
    (void) av;
    (void) env;
    if (ac != 1)
	    return (127);
    my_minishell(env);
}