/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandom <aandom@student.abudhabi42.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 19:20:51 by aandom            #+#    #+#             */
/*   Updated: 2023/06/10 17:14:20 by aandom           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parse.h"

int	all_space(char *str)
{
	int	i;

	i = 0;
	while (str [i])
	{
		if (!ft_isspace(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static void	change_to_quote(t_lexer **token, int *i)
{
	char	c;

	c = (*token)->str[*i];
	if (c == '\'')
		(*token)->quote = SINGLE;
	else if (c == '\"')
		(*token)->quote = DOUBLE;
	(*i)++;
}

static int	change_to_noquote(t_lexer **token, int *i)
{
	char	c;
	int		q;

	c = (*token)->str[*i];
	q = (*token)->quote;
	if ((c == '\'' && q == SINGLE) || (c == '\"' && q == DOUBLE))
	{
		(*token)->quote = NOQUOTE;
		(*i)++;
		return (1);
	}
	return (0);
}

static void	trim_quote(t_lexer **token)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	str = malloc(sizeof(char) * (count_len((*token)->str, 0, 0) + 1));
	if (!str)
		return ;
	while ((*token)->str[i])
	{
		if (is_quote(token, i))
		{
			change_to_quote(token, &i);
			continue ;
		}
		else if (change_to_noquote(token, &i))
			continue ;
		str[j++] = (*token)->str[i++];
	}
	str[j] = '\0';
	free((*token)->str);
	(*token)->str = str;
	return ;
}

void	remove_quotes(t_lexer **lexed)
{
	t_lexer	*tmp;

	tmp = *lexed;
	while (tmp && tmp->str && tmp->type != END)
	{
		if (inside_quote(tmp->str) && (!tmp->prev || \
			(tmp->prev && tmp->prev->type != LESS_LESS)))
			trim_quote(&tmp);
		tmp = tmp->next;
	}
}
