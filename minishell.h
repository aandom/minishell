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
# include <readline/readline.h>
# include <readline/history.h>
# include "/usr/include/readline/readline.h"
# include "/usr/include/readline/history.h"
# include <sys/fcntl.h>
# include <limits.h>
#include <fcntl.h>
# include <sys/wait.h>
# include <errno.h>

# define PROMPT "\033[0;32m[Minishell]~$ \x1B[0m"

extern int	exit_code;

enum tokentype
{
    PIPE = 1,
    GREAT,
    LESS,
    GREAT_GREAT,
    LESS_LESS,
    WORD,
    STAB,
    VAR,
    END,
};

enum quotes
{
    NOQUOTE,
    SINGLE,
    DOUBLE,
};

typedef struct s_evar
{
    char    *key;
    char    *value;
    struct s_evar   *next; 
}           t_evar;

typedef struct s_iofiles
{
    char    *infile;
    char    *outfile;
    int     fdin;
    int     fdout;
    int     stdin_cp;
    int     stdout_cp;
    char    *here_delimter;
    int     here_quote;
}   t_iofiles;


typedef struct s_lexer
{
    char    *str;
    int     type;
    int     is_var;
    int     index;
    int     quote;
    struct s_lexer *prev;
    struct s_lexer *next;
}       t_lexer;

typedef struct s_cmd
{
    char            *cmd;
    char            **cmdarg;
    char            *path;
    int             pipeout;
    int             pipein;
    int             *tube;
    t_iofiles       *iofiles;
    struct s_cmd    *prev;
    struct s_cmd    *next;
}       t_cmd;

typedef struct s_data
{
    char        *input;
    char        **env;
    char        **wdir;
    pid_t       pid;
    t_cmd       *cmds;
    t_lexer     *lexed;
    t_evar      *envar;
}       t_data;


char	**clean(char **av);
char	**ft_split(char *str, char c);
int     ft_parser(t_data *data);
size_t	ft_strlen(const char *s);
void    remove_quotes(t_lexer **lexed);
int     inside_quote(char *str);
int     check_quote(char *str, int i, int  quote);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strdup(const char *src);
void	*ft_memcpy(void *dest, const void *src, size_t n);
char	*ft_strtrim(char const *s1, unsigned char set);
void	extract_command(t_data *data, t_lexer *lexed);
t_cmd	*get_last_cmd(t_cmd *cmd);
t_cmd	*new_cmd(int pipeout);
void	add_back_cmd(t_cmd **cmds, t_cmd *cmd);
void	ft_heredoc(t_data *data, t_cmd **cmds, t_lexer **token);
char	*ft_itoa(int n);
char	*ft_strjoin(char const *s1, char const *s2);
int     ft_strncmp(const char *s1, const char *s2, size_t n);
void    initialize_iofds(t_cmd  *cmd);
int     remove_prev_iofds(t_iofiles *iofds, int code);
void	ft_read_from(t_data *data,t_cmd **cmds, t_lexer **token);
void	ft_append(t_data *data, t_cmd **cmds, t_lexer **token);
void    ft_redirect(t_data *data, t_cmd **cmds, t_lexer **token);
void    ft_pipe(t_data *data, t_cmd **cmds, t_lexer **token);
void	*ft_memset(void *s, int c, size_t n);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
void    copy_env(t_data *data, char **env);
void	*ft_memchr(const void *str, int c, size_t n);
char	*ft_strchr(const char *s, int c);
int     ft_execute(t_data *data);

void    ft_expand(t_data *data);

void	ft_lst_clear_token(t_lexer **lst, void (*del)(void*));
void    voidfree(void *ptr);
void	ft_arr_freer(char **str);
void	ft_free_iofile(t_iofiles *iofiles);
void	ft_lst_clear_cmd(t_cmd **lst, void (*del)(void*));
int     ft_isdigit(int c);
int     ft_isalpha(int c);
int     ft_isalnum(int c);
int     ft_expand_var(t_data *data, t_lexer **token);
int     is_next_char_sep(char *str, int i);
char    *extract_var_value(t_lexer *token, int i, t_data *data);
char    *get_varname(char   *str);
int     var_in_env(t_evar *envar, char *key);
char    *get_varvalue(t_evar *evar, char *key);
int     get_var_len(char *str);
char    *copy_token_str(char *str, char *value, int index, int len);

void	ft_lst_clear_token(t_lexer **lst, void (*del)(void*));
void	ft_lst_clear_cmd(t_cmd **lst, void (*del)(void*));
int     initialize_envar(t_data *data, char **env);
void    close_iofds(t_cmd *cmds, int code);
int     ft_isspace(int c);
void    exitshell(t_data *data, int excode);
int     ft_exit(t_data *data, char **args);
int     ft_strcmp(const char *s1, const char *s2);



int	    ft_cd(t_evar *env, t_cmd *cmd);
int 	ft_pwd();
int		ft_unset(t_data *data, t_cmd *cmd);
int		ft_export(t_data *d);
int 	execute_builtin(t_data *data, t_cmd *cmd);
int	    is_builtin(char *str);
void	ft_env(t_evar *env);
int 	ft_echo(t_cmd *cmd);


void	ft_putendl_fd(char *s, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putchar_fd(char c, int fd);

void	expecting_input(void);
void	ft_bzero(void *s, size_t n);
void	not_expecting_input(void);

void	env_pointer(t_data *data);
void	sort_env(char **tab, int env_len);
int	    ft_envlen(t_evar *env);

# endif