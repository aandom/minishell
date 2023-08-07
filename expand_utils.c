/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandom <aandom@student.abudhabi42.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 22:49:10 by aandom            #+#    #+#             */
/*   Updated: 2023/08/07 22:49:10 by aandom           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_quotes(t_lexer **token, char c)
{
	if (c == '\'' && (*token)->quote == NOQUOTE)
		(*token)->quote = SINGLE;
	else if (c == '\"' && (*token)->quote == NOQUOTE)
		(*token)->quote = DOUBLE;
	else if ((c == '\'' && (*token)->quote == SINGLE)
		|| (c == '\"' && (*token)->quote == DOUBLE))
		(*token)->quote = NOQUOTE;
}

int	is_next_char_sep(char *str, int i)
{
	if (str[i] == ' ' || str[i] == '$' || str[i] == '=' || str[i] == '\0')
		return (1);
	return (0);
}

int	is_valid_expansion(t_lexer *token, int i)
{
	if (is_next_char_sep(token->str, i + 1))
		return (0);
	if (i > 1 && (token->str[i - 1] == '\"' && token->str[i + 1] == '\"'))
		return (0);
	if (token->quote == SINGLE)
		return (0);
	return (1);
}

int	var_len(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i] && str[i] != '$')
		i++;
	i++;
	if (ft_isdigit(str[i]) || str[i] == '?')
		return (count + 1);
	while (str[i])
	{
		if (ft_isalnum(str[i]) || str[i] == '-')
		{
			i++;
			count++;
		}
		else
			break ;
	}
	return (count);
}

char	*get_varname(char *str)
{
	int		start;
	int		len;
	char	*varname;

	start = 0;
	while (str[start])
	{
		if (str[start] == '$')
		{
			start = start + 1;
			break ;
		}
		start++;
	}
	len = var_len(str);
	varname = ft_substr(str, start, len);
	if (!varname)
		return (NULL);
	return (varname);
}
