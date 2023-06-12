/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandom <aandom@student.abudhabi42.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 14:11:03 by aandom            #+#    #+#             */
/*   Updated: 2023/06/12 16:03:49 by aandom           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>

# define PROMPT "\033[0;32m [Minishell]~$ \x1B[0m"

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

typedef struct s_iofiles
{
    int infile;
    int outfile;
}   t_iofiles;


typedef struct s_lexer
{
    char    *str;
    int     type;
    int     index;
    struct s_lexer *prev;
    struct s_lexer *next;
}       t_lexer;

typedef struct s_cmdtable
{
    char    *cmd;
    char    **cmdarg;
    char    *path;
    t_iofiles file;
    struct t_cmdtable *prev;
    struct t_cmdtable *next;
}       t_cmdtable;

typedef struct s_data
{
    char        *input;
    char        **env;
    char        **wdir;
    t_cmdtable  *cmds;
    t_lexer     *lexed;
}       t_data;


char	**clean(char **av);
char	**ft_split(char *str, char c);
void    ft_parser(t_data *data);
size_t	ft_strlen(const char *s);
void    remove_quotes(t_lexer **lexed);
int     inside_quote(char *str);
int     check_quote(char *str, int i, int  quote);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strdup(const char *src);
void	*ft_memcpy(void *dest, const void *src, size_t n);
char	*ft_strtrim(char const *s1, unsigned char set);


# endif