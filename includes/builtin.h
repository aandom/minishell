/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandom <aandom@student.abudhabi42.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 17:47:39 by aandom            #+#    #+#             */
/*   Updated: 2024/01/01 17:47:39 by aandom           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "minishell.h"

// builtins.c
int			is_builtin(char *str);
int			execute_builtin(t_data *data, t_cmd *cmd, t_exno *ex_no);

// env_pointer.c
int			ft_envlen(t_evar *env);
void		env_pointer(t_data *data);
void		sort_env(char **tab, int env_len);

// envar_utils.c
t_evar		*new_evar(char *str);
void		copy_env(t_data *data, char **env);
int			env_var_len(char **env);
t_evar		*find_evar(t_evar *env, char *key);

// envar.c
char		*extract_key(char *str, int *i);
char		*extract_value(char *str);
void		add_back_env(t_evar **evar, t_evar *newvar);
void		ft_del_env(t_evar **head, char *str);
int			initialize_envar(t_data *data, char **env);

// ft_cd_utils
int			arg_counter(char **cmd);

// ft_cd.c
int			ft_cd_new(t_data *d, t_cmd *cmd);

// ft_echo.c
int			ft_echo(t_cmd *cmd);

// ft_env.c
int			ft_env(t_cmd *cmd, t_evar *env);

// ft_exit_utils.c
int			set_sign(const char *str, int *sign, int i);
long long	ft_atoi_lu(char *str, int *is_valid);

// ft_exit.c
int			ft_exit(t_data *data, char **args, t_exno *ex_no);

// ft_export_utils.c
void		ft_putendl_fd2(char *str, int fd);
int			is_invalid_key(char *str);
int			ft_already_exit(t_evar *env, char *str);

// ft_export.c
int			ft_export(t_data *d);
int			ft_export_util(t_data *d);
void		ft_var_freer(t_evar *env);

// ft_new_env.c
void		update_wds(t_data *data, char *wd);

// ft_pwd.c
int			ft_pwd(t_data *data);

// ft_shlvl.c
void		ft_shlvl(t_data *data, t_evar *env);
int			init_wds(t_data *data);

// ft_unset.c
int			ft_unset(t_data *data, t_cmd *cmd);

#endif