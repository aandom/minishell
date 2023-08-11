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
// # include "/usr/include/readline/readline.h"
// # include "/usr/include/readline/history.h"
# include <sys/fcntl.h>
# include <limits.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <errno.h>
# include <sys/stat.h>
# include <stdint.h>

# define PROMPT "\033[0;32m[Minishell]~$ \x1B[0m"
# define QERRMSG "unexpected EOF while looking for matching `"
# define TOK_ERR "syntax error near unexpected token `"
# define INVARG "numeric argument required"
# define CD_ERR "cd: error retrieving current directory"
# define CD_ERR2 "getcwd: cannot access parent directories"

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

typedef	struct s_exno
{
	int	exno;
}		t_exno;


typedef struct s_evar
{
	char			*key;
	char			*value;
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


void	*ft_calloc(size_t count, size_t size);
void	free_evar_list(t_evar *head);
char	**clean(char **av);
char	**ft_split(char *str, char c);
int		ft_parser(t_data *data);
size_t	ft_strlen(const char *s);
void	remove_quotes(t_lexer **lexed);
int		inside_quote(char *str);
int		check_quote(char *str, int i, int quote);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strdup(const char *src);
void	*ft_memcpy(void *dest, const void *src, size_t n);
char	*ft_strtrim(const char *s1, const char *set);
void	extract_command(t_data *data, t_lexer *lexed);
t_cmd	*get_last_cmd(t_cmd *cmd);
t_cmd	*new_cmd(int pipeout);
void	add_back_cmd(t_cmd **cmds, t_cmd *cmd);
void	ft_heredoc(t_data *data, t_cmd **cmds, t_lexer **token);
char	*ft_itoa(int n);
char	*ft_strjoin(char *s1, char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	initialize_iofds(t_cmd *cmd);
int		remove_prev_iofds(t_iofiles *iofds, int code);
void	ft_pipe(t_data *data, t_cmd **cmds, t_lexer **token);
void	*ft_memset(void *s, int c, size_t n);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
void	copy_env(t_data *data, char **env);
void	*ft_memchr(const void *str, int c, size_t n);
char	*ft_strchr(const char *s, int c);
// int		ft_execute(t_data *data);
char	*ft_strrchr(const char *s, int c);

void	ft_expand(t_data *data);

void	ft_lst_clear_token(t_lexer **lst, void (*del)(void*));
void	voidfree(void *ptr);
void	ft_arr_freer(char **str);
void	ft_free_iofile(t_iofiles *iofiles);
void	ft_lst_clear_cmd(t_cmd **lst, void (*del)(void*));
int		ft_isdigit(int c);
int		ft_isalpha(int c);
int		ft_isalnum(int c);
// int		ft_expand_var(t_data *data, t_lexer **token);
int		is_next_char_sep(char *str, int i);
// char	*extract_var_value(t_lexer *token, int i, t_data *data);
char	*get_varname(char *str);
int		var_in_env(t_evar *envar, char *key);
char	*get_varvalue(t_evar *evar, char *key);
int		var_len(char *str);
char	*copy_token_str(char *str, char *value, int index, int len);

void	ft_lst_clear_token(t_lexer **lst, void (*del)(void*));
void	ft_lst_clear_cmd(t_cmd **lst, void (*del)(void*));
int		initialize_envar(t_data *data, char **env);
void	close_iofds(t_cmd *cmds, int code);
int		ft_isspace(int c);
void	exitshell(t_data *data, int excode);
// int		ft_exit(t_data *data, char **args);
int		ft_strcmp(const char *s1, const char *s2);
void	ft_putendl_fd(char *s, int fd);
int		print_errmsg(char *cmd, char *info, char *errmsg, int errnum);
void	ft_errmsg(char *msg, char *info, int quote);
int		parsing_check(t_lexer **token);
void	free_all(t_data *data, int code);
int		env_var_len(char **env);

int		ft_cd(t_data *d, t_cmd *cmd);
// int		ft_pwd(void);
int		ft_unset(t_data *data, t_cmd *cmd);
int		ft_export(t_data *d);
// int		execute_builtin(t_data *data, t_cmd *cmd);
int		is_builtin(char *str);
int		ft_env(t_cmd *cmd, t_evar *env);
int		ft_echo(t_cmd *cmd);

void	ft_putendl_fd(char *s, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putchar_fd(char c, int fd);

void	expecting_input(void);
void	ft_bzero(void *s, size_t n);
void	not_expecting_input(void);

void	env_pointer(t_data *data);
void	ft_del_env(t_evar **head, char *str);
void	sort_env(char **tab, int env_len);
int		ft_envlen(t_evar *env);
char	*extract_key(char *str);
char	*extract_value(char *str);
void	add_back_env(t_evar **evar, t_evar *newvar);
t_evar	*new_evar(char *str);
int		initialize_envar(t_data *data, char **env);

void	ft_shlvl(t_data *data, t_evar *env);
int		ft_atoi(const char *str);
int		ft_already_exit(t_evar *env, char *str);


// command_utils.c
void		add_back_cmd(t_cmd **cmds, t_cmd *cmd);
t_cmd		*new_cmd(int pipeout);
t_cmd		*get_last_cmd(t_cmd *cmd);

// command_args.
int			count_args(t_lexer *token);
int			copy_cmdarg(char **cmdarg, char **newarg);
void		fill_cmd_args(t_lexer **token, t_cmd **lastcmd);

// iofds.c
int			ft_check_iofiles(t_iofiles *iofds);
void		reset_stdio(t_iofiles *iofds);
void		close_iofds(t_cmd *cmds, int code);
void		set_iofds(t_iofiles *iofds);

// ft_pipe.c 

void		ft_pipe(t_data *data, t_cmd **cmds, t_lexer **token);
int			create_pipes(t_data *data);
void		close_unused_pipes(t_cmd *headcmd, t_cmd *curcmd);
void		dup_pipe_fds(t_cmd *headcmd, t_cmd *curcmd);

// execute_utils.c
char		**get_splited_path(t_evar *evar);
char		*get_cmd(t_evar *envar, t_cmd *cmd);
int			is_directory(char *cmd);
int			check_command(t_cmd *cmd);
int			check_prepare_exec(t_data *data);

// ft_wait.c
int			fork_wait(t_data *data);

// execute.c
int			exec_cmd_with_nopath(t_data *data, t_cmd *cmd);
int			exec_cmd_with_path(t_data *data, t_cmd *cmd);
// int			execute_cmd(t_data *data, t_cmd *cmd);
// int			create_forks(t_data *data);
// int			ft_execute(t_data *data);


// ft_exit_utils.c
int			check_max(unsigned long long num, int sign, int *is_valid);
int			set_sign(const char *str, int *sign, int i);
long long	ft_atoi_lu(char *str, int *is_valid);

// ft_exit.c
// int			get_exit_code(char *exarg, int *is_valid);
int			exit_with_arg(t_data *data);
// int			ft_exit(t_data *data, char **args);

// ft_heredoc_utils.c
char		*extract_here_val(char *str, int index, t_data *data);
char		*replace_here_val(char *line, char *value, int index);
char		*expand_here_var(char *lineorgin, t_data *data);

// ft_heredoc.c
char		*generate_heredoc_name(void);
int			create_heredoc(t_data *data, t_iofiles *iofds);
int			delim_len(char *str);
int			check_update_delimiter(char **delim);
void		ft_heredoc(t_data *data, t_cmd **cmds, t_lexer **token);

// ft_input.c
void		ft_read_from(t_cmd **cmds, t_lexer **token);

// ft_output.c
void		ft_append(t_cmd **cmds, t_lexer **token);
void		ft_redirect(t_cmd **cmds, t_lexer **token);

// lexer_utils.c
int			inside_quote(char *str);
int			is_quote(t_lexer **token, int i);
int			count_len(char *s, int i, int c);

// lexer.c
void		change_to_quote(t_lexer **token, int *i);
int			change_to_noquote(t_lexer **token, int *i);
void		trim_quote(t_lexer **token);
void		remove_quotes(t_lexer **lexed);

// expand_var.c
void		check_var(t_lexer **token);
char		*get_varvalue(t_evar *evar, char *key);
int			var_in_env(t_evar *envar, char *key);
// char		*extract_var_value(t_lexer *token, int i, t_data *data);
void		delete_var(t_lexer **token, char *str, int index);

// expand_utilis.c
void		update_quotes(t_lexer **token, char c);
int			is_next_char_sep(char *str, int i);
int			is_valid_expansion(t_lexer *token, int i);
int			var_len(char *str);
char		*get_varname(char *str);

// expand.c
void		replace_var(t_lexer **token, char *varvalue, int index);
// int			expand_var(t_data *data, t_lexer **token);
int			check_consecutive(t_lexer *token);
int			parsing_check(t_lexer **token);
// int			ft_expand_var(t_data *data, t_lexer **token);

// expand_var_utils.c
char		*copy_token_str(char *str, char *value, int index, int len);
void		update_var(t_lexer **token, char *str, int index, char *value);

// exit_shell.c
void		ft_arr_freer(char **str);
void		ft_free_iofile(t_iofiles *iofiles);
void		free_all(t_data *data, int code);
void		exitshell(t_data *data, int excode);

// ft_token_utils.c
void		ft_add_token_back(t_lexer **tokens, t_lexer *new);
t_lexer		*ft_new_token(char *word, int type);

// ft_token.c
int			extract_word(t_data *data, size_t *i, int start);
void		add_token_to_lexer(t_data *data, size_t idx, int type);
void		add_word_to_lexer(t_data *data, int start, size_t end, int type);

// parser.c
int			check_token(char *str, int i);
int			check_quote(char *str, int i, int quote);
int			ft_parser(t_data *data);

// ft_export
int			ft_already_exit(t_evar *env, char *str);
int			is_invalid_key(char *str);
void		ft_putendl_fd2(char *str, int fd);

// ft_cd_utils
void		ft_expanding_tilda(t_data *data);
t_evar		*find_evar(t_evar *env, char *key);

// signal.c
// void	here_not_expecting_input(void);
// void	herer_expecting_input(void);

void	herer_expecting_input(t_data *data);
void	here_not_expecting_input(t_data *data);


int	get_exit_code(char *exarg, int *is_valid, t_exno *ex_no);
int	ft_exit(t_data *data, char **args, t_exno *ex_no);
int	ft_expand_var(t_data *data, t_lexer **token, t_exno *ex_no);
int	expand_var(t_data *data, t_lexer **token, t_exno *ex_no);
char	*extract_var_value(t_lexer *token, int i, t_data *data, t_exno *ex_no);
int		execute_builtin(t_data *data, t_cmd *cmd, t_exno *ex_no);
int		create_forks(t_data *data, t_exno *ex_no);
int		execute_cmd(t_data *data, t_cmd *cmd, t_exno *ex_no);
int		ft_execute(t_data *data, t_exno *ex_no);

// fd_cd2.c
int	init_wds(t_data *data);
int	ft_cd_new(t_data *d, t_cmd *cmd);
void	update_pwd(t_data *data, char *key, char *value);
void	pwd(t_evar *env, char *key);
int	ft_pwd(t_data *data);



#endif