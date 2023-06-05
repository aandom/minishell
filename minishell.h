/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandom <aandom@student.abudhabi42.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 14:11:03 by aandom            #+#    #+#             */
/*   Updated: 2023/06/05 14:46:04 by aandom           ###   ########.fr       */
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
    END,
    WORD,
    STAB,
};

enum quotes
{
    NONE,
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
    struct t_lexer *next;
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


# endif