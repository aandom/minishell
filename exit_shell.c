/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandom <aandom@student.abudhabi42.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 01:22:40 by aandom            #+#    #+#             */
/*   Updated: 2023/08/08 01:22:40 by aandom           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_arr_freer(char **str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		voidfree(str[i]);
		i++;
	}
	voidfree(str);
}

void	ft_free_iofile(t_iofiles *iofiles)
{
	if (!iofiles)
		return ;
	if (iofiles->infile)
	{
		if (iofiles->fdin != -1)
			close(iofiles->fdin);
		free(iofiles->infile);
	}
	if (iofiles->outfile)
	{
		if (iofiles->fdout != -1)
			close(iofiles->fdout);
		free(iofiles->outfile);
	}
	if (iofiles->h_delim)
	{
		free(iofiles->h_delim);
		// unlink(iofiles->infile);
	}
	free(iofiles);
}

void	free_all(t_data *data, int code)
{
	if (data && data->input)
		voidfree(data->input);
	if (data && data->lexed)
		ft_lst_clear_token(&data->lexed, &voidfree);
	if (data && data->cmds)
		ft_lst_clear_cmd(&data->cmds, &voidfree);
	if (code == 1)
	{
		if (data && data->env)
			ft_arr_freer(data->env);
		rl_clear_history();
	}
}

void	exitshell(t_data *data, int excode)
{
	if (data)
	{
		if (data->cmds && data->cmds->iofiles)
			close_iofds(data->cmds, 1);
		free_all(data, 1);
		if (data && data->envar)
			free_evar_list(data->envar);
		if (data && data->pwd)
			voidfree(data->pwd);
		if (data && data->oldpwd)
			voidfree(data->oldpwd);
		voidfree(data);
	}
	exit(excode);
}
