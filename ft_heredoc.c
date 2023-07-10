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

char    *generate_heredoc_name()
{
    static int  i = 1;
    char    *name;
    char    *identifier;

    identifier = ft_itoa(i);
    name = ft_strjoin("/tmp/.m_heredoc_", identifier);
    free(identifier);
    i++;
    return(name);
}

int create_heredoc(t_data *data, t_iofiles *iofds)
{
    int     fd;
    int     i;
    char    *line;

    fd = open(iofds->infile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    while (1)
	{
		line = readline(">");
		if (!ft_strncmp(line, iofds->here_delimter, ft_strlen(iofds->here_delimter)))
			break ;
		else
        {
			write(fd, line, ft_strlen(line));
            write(fd, "\n", 1);
        }
		free(line);
	}
	close(fd);
	free(line);
	return (1);
}

void	ft_heredoc(t_data *data, t_cmd **cmds, t_lexer **token)
{
	t_cmd       *lastcmd;
    t_lexer     *tmp;
    t_iofiles   *iofds;

    lastcmd = get_last_cmd(*cmds);
    tmp = *token;
    initialize_iofds(lastcmd);
    iofds = lastcmd->iofiles;
    if (!remove_prev_iofds(iofds, 1))
        return ;
    iofds->here_delimter = ft_strdup(tmp->next->str);
    iofds->infile = generate_heredoc_name();
    if(create_heredoc(data, iofds))
        iofds->fdin = open(iofds->infile, O_RDONLY);
    else
        iofds->fdin = -1;
    tmp = tmp->next->next;
    *token = tmp;
}