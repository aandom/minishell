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

int	create_heredoc(t_data *data, t_iofiles *iofds)
{
	int		fd;
	char	*line;
	char	*tmp;

	fd = open(iofds->infile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	while (1)
	{
		line = readline(">");
		if (!line)
		{
			printf ("warning: here-document delimited by end-of-file (wanted `%s')\n", iofds->h_delim);
			break ;
		}
		if (!ft_strncmp(line, iofds->h_delim, ft_strlen(iofds->h_delim)))
			break ;
		else if (iofds->here_quote != 1)
		{
			tmp = expand_here_var(line, data);
			// voidfree(line);
			line = tmp;
		}
		ft_putendl_fd(line, fd);
		free(line);
	}
	close(fd);
	return (free(line), 1);
}

int	delim_len(char *str)
{
	int	i;
	int	c;

	i = -1;
	c = 0;
	while (str[++i])
	{
		if (str[i] != '\'' && str[i] != '\"')
			c++;
	}
	return (c);
}

int	check_update_delimiter(char **delim)
{
	int		i;
	char	*d;
	char	*str;

	i = 0;
	str = *delim;
	if (!ft_strchr(*delim, '\'') && !ft_strchr(*delim, '\"'))
		return (0);
	d = (char *)malloc(sizeof(char) * delim_len(*delim) + 1);
	if (!d)
		return (0);
	while (str && *str)
	{
		if (*str != '\"' && *str != '\'')
		{
			d[i] = *str;
			i++;
		}
		str++;
	}
	d[i] = '\0';
	voidfree(*delim);
	*delim = d;
	return (1);
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
	iofds->here_quote = check_update_delimiter(&iofds->h_delim);
	iofds->infile = generate_heredoc_name();
	if (create_heredoc(data, iofds))
		iofds->fdin = open(iofds->infile, O_RDONLY);
	else
		iofds->fdin = -1;
	tmp = tmp->next->next;
	*token = tmp;
}
