/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandom <aandom@student.abudhabi42.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 21:45:03 by aandom            #+#    #+#             */
/*   Updated: 2023/08/07 21:45:03 by aandom           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*extract_here_val(char *str, int index, t_data *data)
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

static char	*delete_here_var(char *str, int index)
{
	char	*newstr;
	int		len;
	int		i;
	int		j;

	i = 0;
	j = 0;
	len = ft_strlen(str) - var_len(str + index);
	newstr = malloc (sizeof(char) * (len + 1));
	if (!newstr)
		return (NULL);
	while (str[i])
	{
		if (i == index && str[i] == '$')
		{
			i = i + var_len(str + index) + 1;
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

static char	*update_here_var(char *str, int index, char *value)
{
	char	*newstr;
	int		len;

	len = ft_strlen(str) - var_len(str + index) + ft_strlen(value);
	newstr = copy_token_str(str, value, index, len);
	return (newstr);
}

char	*replace_here_val(char *line, char *value, int index)
{
	char	*new;

	if (value == NULL)
		new = delete_here_var(line, index);
	else
		new = update_here_var(line, index, value);
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
