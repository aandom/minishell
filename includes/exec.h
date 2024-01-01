/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandom <aandom@student.abudhabi42.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 17:47:53 by aandom            #+#    #+#             */
/*   Updated: 2024/01/01 17:47:53 by aandom           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "minishell.h"

// execute_fin_cmd.c
int			exec_cmd_with_nopath(t_data *data, t_cmd *cmd);
int			exec_cmd_with_path(t_data *data, t_cmd *cmd);

// execute_utils.c;
int			check_prepare_exec(t_data *data);
char		*get_cmd(t_evar *envar, t_cmd *cmd);
int			is_directory(char *cmd);
int			check_command(t_cmd *cmd);

// execute.c
int			ft_execute(t_data *data, t_exno *ex_no);

// ft_pipe.c 
void		ft_pipe(t_data *data, t_cmd **cmds, t_lexer **token);
int			create_pipes(t_data *data);
void		close_unused_pipes(t_cmd *headcmd, t_cmd *curcmd);
void		dup_pipe_fds(t_cmd *headcmd, t_cmd *curcmd);

// ft_wait.c
int			fork_wait(t_data *data);

// iofds.c
int			ft_check_iofiles(t_iofiles *iofds);
void		reset_stdio(t_iofiles *iofds);
void		close_iofds(t_cmd *cmds, int code);
void		set_iofds(t_iofiles *iofds);

#endif