/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandom <aandom@student.abudhabi42.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 17:48:24 by aandom            #+#    #+#             */
/*   Updated: 2024/01/01 17:48:24 by aandom           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "minishell.h"

// clean_cmd.c
void		voidfree(void *ptr);
void		ft_lst_clear_cmd(t_cmd **lst, void (*del)(void*));

// clean_token.c
void		ft_lst_clear_token(t_lexer **lst, void (*del)(void*));

// error.c
int			errmsg(char *cmd, char *info, char *errmsg, int errnum);
void		ft_errmsg(char *msg, char *info, int quote);

// exit_shell.c
void		ft_arr_freer(char **str);
void		ft_free_iofile(t_iofiles *iofiles);
void		free_all(t_data *data, int code);
void		exitshell(t_data *data, int excode);

// ft_free.c
void		free_evar_list(t_evar **head);
void		ft_lst_clear_tvar(t_evar **lst, void (*del)(void*));
char		**clean(char **av);

// ft_strcmp.c
int			ft_strcmp(const char *s1, const char *s2);

// signals_2.c
void		ignore_sigquit(void);
void		set_signals_interactive(void);
void		set_signals_noninteractive(void);

// signals.c
void		child_signals( void);
int			init_signals(void);

#endif