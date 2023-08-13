/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandom <aandom@student.abudhabi42.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 07:59:57 by aandom            #+#    #+#             */
/*   Updated: 2023/07/06 07:59:57 by aandom           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*generate_heredoc_name(void)
{
	static int	i;
	char		*name;
	char		*identifier;

	identifier = ft_itoa(i);
	name = ft_strjoin(ft_strdup("/tmp/.m_heredoc_"), identifier);
	free(identifier);
	i++;
	return (name);
}

void	print_here_err(char	*here)
{
	char	*errmsg;

	errmsg = ft_strjoin(ft_strdup("minishell: "), HR_ERR);
	errmsg = ft_strjoin(errmsg, "(wanted `");
	errmsg = ft_strjoin(errmsg, here);
	errmsg = ft_strjoin(errmsg, "')");
	ft_putendl_fd(errmsg, STDERR_FILENO);
	free(errmsg);
}

int	create_heredoc(t_data *data, t_iofiles *iofds)
{
	int		fd;
	char	*line;
	char	*tmp;

	fd = open(iofds->infile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	while (1 && g_exit_code != STOP_HEREDOC)
	{
		line = readline(">");
		if (!line)
		{
			rl_redisplay();
			print_here_err(iofds->h_delim);
			break ;
		}
		if (!ft_strcmp(line, iofds->h_delim))
			break ;
		else if (iofds->here_quote != 1)
		{
			tmp = expand_here_var(line, data);
			line = tmp;
		}
		ft_putendl_fd(line, fd);
		free(line);
	}
	return (close(fd), 1);
}

void	ft_heredoc(t_data *data, t_cmd **cmds, t_lexer **token)
{
	t_cmd		*lastcmd;
	t_lexer		*tmp;
	t_iofiles	*iofds;

	lastcmd = get_last_cmd(*cmds);
	tmp = *token;
	initialize_iofds(lastcmd);
	iofds = lastcmd->iofiles;
	if (!remove_prev_iofds(iofds, 1))
		return ;
	iofds->h_delim = ft_strdup(tmp->next->str);
	g_exit_code = IN_HEREDOC;
	iofds->here_quote = check_update_delimiter(&iofds->h_delim);
	iofds->infile = generate_heredoc_name();
	if (create_heredoc(data, iofds))
		iofds->fdin = open(iofds->infile, O_RDONLY);
	else
		iofds->fdin = -1;
	if (g_exit_code == STOP_HEREDOC)
		while (tmp && tmp->type != END)
			tmp = tmp->next;
	else
		tmp = tmp->next->next;
	*token = tmp;
}
