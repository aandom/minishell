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
# include "../libft/libft.h"
# include "structs.h"
# include "utils.h"
# include "token.h"
# include "parse.h"
# include "exec.h"
# include "builtin.h"

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

#endif