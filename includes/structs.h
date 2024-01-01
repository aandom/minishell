/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandom <aandom@student.abudhabi42.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 18:22:06 by aandom            #+#    #+#             */
/*   Updated: 2024/01/01 18:22:06 by aandom           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include <unistd.h>
# include <sys/wait.h>

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

#endif