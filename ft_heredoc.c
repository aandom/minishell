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

	i = 1;
	identifier = ft_itoa(i);
	name = ft_strjoin("/tmp/.m_heredoc_", identifier);
	free(identifier);
	i++;
	return (name);
}

char	*extract_here_val(char *str, int index, t_data *data)
{
	char	*varname;
	char	*varvalue;

	varname = get_varname(str + index);
	if (varname && var_in_env(data->envar, varname))
		varvalue = get_varvalue(data->envar, varname);
	else if (varname && varname[0] == '?')
		varvalue = NULL;
	else
		varvalue = NULL;
	return (varvalue);
}

static char	*delete_var(char *str, int index)
{
	char	*newstr;
	int		len;
	int		i;
	int		j;

	i = 0;
	j = 0;
	len = ft_strlen(str) - get_var_len(str + index);
	newstr = malloc (sizeof(char) * (len + 1));
	if (!newstr)
		return (NULL);
	while (str[i])
	{
		if (i == index && str[i] == '$')
		{
			i = i + get_var_len(str + index) + 1;
			if (str[i] == '\0')
				break ;
		}
		newstr[j] = str[i];
		i++;
		j++;
	}
	newstr[j] = '\0';
	return (newstr);
}

static char	*update_var(char *str, int index, char *value)
{
	char	*newstr;
	int		len;

	len = ft_strlen(str) - get_var_len(str + index) + ft_strlen(value);
	newstr = copy_token_str(str, value, index, len);
	return (newstr);
}

char	*replace_here_val(char *line, char *value, int index)
{
	char	*new;

	if (value == NULL)
		new = delete_var(line, index);
	else
		new = update_var(line, index, value);
	return (new);
}

char	*expand_here_var(char *lineorgin, t_data *data)
{
	char	*newline;
	char	*line;
	int		i;
	char	*value;

	i = 0;
	line = ft_strdup(lineorgin);
	while (line && line[i])
	{
		if (line[i] == '$' && is_next_char_sep(line, i))
		{
			value = extract_here_val(line, i, data);
			newline = replace_here_val(line, value, i);
			voidfree (line);
			line = newline;
		}
		else
			i++;
	}
	return (line);
}

int	create_heredoc(t_data *data, t_iofiles *iofds)
{
	int		fd;
	int		i;
	char	*line;
	char	*tmp;

	fd = open(iofds->infile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	while (1)
	{
		line = readline(">");
		if (!line)
		{
			printf ("warning: here-document delimited by end-of-file (wanted `%s')\n", iofds->here_delimter);
			break;
		}
		if (!ft_strncmp(line, iofds->here_delimter, ft_strlen(iofds->here_delimter)))
			break ;
		else if (iofds->here_quote != 1)
		{
			tmp = expand_here_var(line, data);
			// line = expand_here_var(line, data);
			// voidfree(line);
			line = tmp;
		}
		ft_putendl_fd(line, fd);
		free(line);
	}
	close(fd);
	free(line);
	return (1);
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
	iofds->here_delimter = ft_strdup(tmp->next->str);
	iofds->here_quote = check_update_delimiter(&iofds->here_delimter);
	iofds->infile = generate_heredoc_name();
	if (create_heredoc(data, iofds))
		iofds->fdin = open(iofds->infile, O_RDONLY);
	else
		iofds->fdin = -1;
	tmp = tmp->next->next;
	*token = tmp;
}
