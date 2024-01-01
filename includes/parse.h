/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandom <aandom@student.abudhabi42.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 17:48:08 by aandom            #+#    #+#             */
/*   Updated: 2024/01/01 17:48:08 by aandom           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "minishell.h"

// command_args.
void		fill_cmd_args(t_lexer **token, t_cmd **lastcmd);

// command_utils.c
void		add_back_cmd(t_cmd **cmds, t_cmd *cmd);
t_cmd		*new_cmd(int pipeout);
t_cmd		*get_last_cmd(t_cmd *cmd);

// command.c
void		extract_command(t_data *data, t_lexer *lexed);

// expand_utils.c
int			is_next_char_sep(char *str, int i);
int			var_len(char *str);
char		*get_varname(char *str);

// expand_var_utils.c
char		*copy_token_str(char *str, char *value, int index, int len);
void		update_var(t_lexer **token, char *str, int index, char *value);

// expand_var.c
void		check_var(t_lexer **token);
char		*get_varvalue(t_evar *evar, char *key);
int			var_in_env(t_evar *envar, char *key);
char		*ex_var_val(t_lexer *token, int i, t_data *data, t_exno *ex_no);
void		delete_var(t_lexer **token, char *str, int index);

// expand.c
int			expand_var(t_data *data, t_lexer **token, t_exno *ex_no);
int			ft_expand_var(t_data *data, t_lexer **token, t_exno *ex_no);

// ft_heredoc_utils2.c
int			check_update_delimiter(char **delim);

// ft_heredoc_utils.c
char		*expand_here_var(char *lineorgin, t_data *data);

// ft_heredoc.c
void		ft_heredoc(t_data *data, t_cmd **cmds, t_lexer **token);

// ft_input.c
void		ft_read_from(t_cmd **cmds, t_lexer **token);

// ft_iofds.c
void		initialize_iofds(t_cmd *cmd);
int			remove_prev_iofds(t_iofiles *iofds, int code);

// ft_output.c
void		ft_append(t_cmd **cmds, t_lexer **token);
void		ft_redirect(t_cmd **cmds, t_lexer **token);

// parser.c
int			check_quote(char *str, int i, int quote);
int			parse_input(t_data *data, t_exno *ex_no);

// quote_utils.c
int			inside_quote(char *str);
int			is_quote(t_lexer **token, int i);
int			count_len(char *s, int i, int c);

// quote.c
int			all_space(char *str);
void		remove_quotes(t_lexer **lexed);

#endif