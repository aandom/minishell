/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandom <aandom@student.abudhabi42.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 14:11:03 by aandom            #+#    #+#             */
/*   Updated: 2023/06/27 15:40:53 by aandom           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/fcntl.h>
# include <limits.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <errno.h>
# include <sys/stat.h>
# include <stdint.h>
# include "./libft/libft.h"

# define PROMPT "\033[0;32m[Minishell]~$ \x1B[0m"
# define QERRMSG "unexpected EOF while looking for matching `"
# define TOK_ERR "syntax error near unexpected token `"
# define INVARG "numeric argument required"
# define CD_ERR "cd: error retrieving current directory"
# define CD_ERR2 "getcwd: cannot access parent directories"
# define HR_ERR "warning: here-document at line 1 delimited by end-of-file "
# define NFE "No such file or directory"
# define EXP_ERR "not a valid identifier"
# define NO_HOME "HOME not set"
# define NO_OPWD "OLDPWD not set"

# ifndef MAX_PATH
#  define MAX_PATH 4096
# endif

extern int	g_exit_code;

enum e_tokentype
{
	WORD = 1,
	STAB,
	PIPE,
	GREAT,
	LESS,
	GREAT_GREAT,
	LESS_LESS,
	END
};

enum e_quotes
{
	NOQUOTE,
	SINGLE,
	DOUBLE,
};

typedef struct s_exno
{
	int	exno;
}		t_exno;

typedef enum e_status
{
	IN_MINI = 10,
	IN_CMD = 20,
	IN_HEREDOC = 40,
	CTRL_C = 130,
	CTRL_BS = 131,
	STOP_HEREDOC = 1,
}	t_g_status_code;

typedef struct s_evar
{
	char			*key;
	char			*value;
	int				stat;
	struct s_evar	*next;
}	t_evar;

typedef struct s_iofiles
{
	char	*infile;
	char	*outfile;
	int		fdin;
	int		fdout;
	int		stdin_cp;
	int		stdout_cp;
	char	*h_delim;
	int		here_quote;
}	t_iofiles;

typedef struct s_lexer
{
	char			*str;
	int				type;
	int				is_var;
	int				index;
	int				quote;
	struct s_lexer	*prev;
	struct s_lexer	*next;
}	t_lexer;

typedef struct s_cmd
{
	char			*cmd;
	char			**cmdarg;
	char			*path;
	int				pipeout;
	int				pipein;
	int				*tube;
	t_iofiles		*iofiles;
	struct s_cmd	*prev;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_data
{
	int			e_code;
	char		*input;
	char		**env;
	char		**wdir;
	char		*pwd;
	char		*oldpwd;
	pid_t		pid;
	t_cmd		*cmds;
	t_lexer		*lexed;
	t_evar		*envar;
}	t_data;

// builtins.c
int			is_builtin(char *str);
int			execute_builtin(t_data *data, t_cmd *cmd, t_exno *ex_no);

// command_args.
void		fill_cmd_args(t_lexer **token, t_cmd **lastcmd);

// command_utils.c
void		add_back_cmd(t_cmd **cmds, t_cmd *cmd);
t_cmd		*new_cmd(int pipeout);
t_cmd		*get_last_cmd(t_cmd *cmd);

// command.c
void		extract_command(t_data *data, t_lexer *lexed);

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

// error.c
int			errmsg(char *cmd, char *info, char *errmsg, int errnum);
void		ft_errmsg(char *msg, char *info, int quote);

// execute_fin_cmd.c
int			exec_cmd_with_nopath(t_data *data, t_cmd *cmd);
int			exec_cmd_with_path(t_data *data, t_cmd *cmd);

// execute_utils.c;
char		*get_cmd(t_evar *envar, t_cmd *cmd);
int			is_directory(char *cmd);
int			check_command(t_cmd *cmd);
int			check_prepare_exec(t_data *data);

// execute.c
int			ft_execute(t_data *data, t_exno *ex_no);

// exit_shell.c
void		ft_arr_freer(char **str);
void		ft_free_iofile(t_iofiles *iofiles);
void		free_all(t_data *data, int code);
void		exitshell(t_data *data, int excode);

// expand_utils.c
void		update_quotes(t_lexer **token, char c);
int			is_next_char_sep(char *str, int i);
int			is_valid_expansion(t_lexer *token, int i);
int			var_len(char *str);
char		*get_varname(char *str);

// expand_var_utils.c
char		*copy_token_str(char *str, char *value, int index, int len);
void		update_var(t_lexer **token, char *str, int index, char *value);

// expand_var.c
void		check_var(t_lexer **token);
char		*get_varvalue(t_evar *evar, char *key);
int			var_in_env(t_evar *envar, char *key);
void		delete_var(t_lexer **token, char *str, int index);
char		*ex_var_val(t_lexer *token, int i, t_data *data, t_exno *ex_no);

// expand.c
int			expand_var(t_data *data, t_lexer **token, t_exno *ex_no);
int			parsing_check(t_lexer **token);
int			ft_expand_var(t_data *data, t_lexer **token, t_exno *ex_no);

// ft_cd_utils
t_evar		*find_evar(t_evar *env, char *key);
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

// ft_free_new.c
void		ft_lst_clear_cmd(t_cmd **lst, void (*del)(void*));
void		ft_lst_clear_token(t_lexer **lst, void (*del)(void*));
void		voidfree(void *ptr);

// ft_free.c
void		free_evar_list(t_evar **head);
char		**clean(char **av);
void		ft_lst_clear_tvar(t_evar **lst, void (*del)(void*));

// ft_heredoc_utils.c
char		*expand_here_var(char *lineorgin, t_data *data);

// ft_heredoc_utils2.c
int			check_update_delimiter(char **delim);

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

// ft_pipe.c 

void		ft_pipe(t_data *data, t_cmd **cmds, t_lexer **token);
int			create_pipes(t_data *data);
void		close_unused_pipes(t_cmd *headcmd, t_cmd *curcmd);
void		dup_pipe_fds(t_cmd *headcmd, t_cmd *curcmd);

// ft_pwd.c
int			ft_pwd(t_data *data);

// ft_shlvl.c
void		ft_shlvl(t_data *data, t_evar *env);
int			init_wds(t_data *data);

// ft_strcmp.c
int			ft_strcmp(const char *s1, const char *s2);

// ft_token_utils.c
void		ft_add_token_back(t_lexer **tokens, t_lexer *new);
t_lexer		*ft_new_token(char *word, int type);

// ft_token.c
int			extract_word(t_data *data, size_t *i, int start);

// ft_unset.c
int			ft_unset(t_data *data, t_cmd *cmd);

// ft_wait.c
int			fork_wait(t_data *data);

// iofds.c
int			ft_check_iofiles(t_iofiles *iofds);
void		reset_stdio(t_iofiles *iofds);
void		close_iofds(t_cmd *cmds, int code);
void		set_iofds(t_iofiles *iofds);

// lexer_utils.c
int			inside_quote(char *str);
int			is_quote(t_lexer **token, int i);
int			count_len(char *s, int i, int c);

// lexer.c
void		remove_quotes(t_lexer **lexed);
int			all_space(char *str);

// parser.c
int			check_token(char *str, int i);
int			check_quote(char *str, int i, int quote);
int			ft_parser(t_data *data);

// signals_2.c
void		ignore_sigquit(void);
void		set_signals_interactive(void);
void		set_signals_noninteractive(void);

// signals.c
void		child_signals( void);
int			init_signals(void);

// ft_new_env.c
void		update_wds(t_data *data, char *wd);

#endif