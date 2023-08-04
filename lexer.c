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

#include "minishell.h"

int	inside_quote(char *str)
{
<<<<<<< HEAD
	if (check_quote(str, 0, NOQUOTE) == SINGLE || check_quote(str, 0, NOQUOTE)
		== DOUBLE)
		return (1);
	return (1);
=======
    int i;

    i = 0;
    while (str[i])
    {
        if (check_quote(str, i, NOQUOTE) == SINGLE || check_quote(str, i, NOQUOTE) == DOUBLE)
            return (1);
        i++;
    }
    return(0);
>>>>>>> 09c3401 (alex ungabunga)
}

int	count_len(char *s)
{
	int	c;
	int	sta;
	int	i;

	i = 0;
	sta = NOQUOTE;
	c = 0;
	while (s && s[i])
	{
		if ((s[i] == '\'' || s[i] == '\"') && sta == NOQUOTE)
		{
			if (s[i] == '\'')
				sta = SINGLE;
			else if (s[i] == '\"')
				sta = DOUBLE;
			i++;
			continue ;
		}
		if ((s[i] == '\'' && sta == SINGLE) || (s[i] == '\"' && sta == DOUBLE))
		{
			sta = NOQUOTE;
			i++;
			continue ;
		}
		c++;
		i++;
	}
	return (c);
}

int	is_quote(t_lexer **token, int i)
{
	char	c;

	c = (*token)->str[i];
	if ((c == '\'' || c == '\"') && (*token)->quote == NOQUOTE)
		return (1);
	return (0);
}

void	change_to_quote(t_lexer **token, int *i)
{
	char	c;

	c = (*token)->str[*i];
	if (c == '\'')
		(*token)->quote = SINGLE;
	else if (c == '\"')
		(*token)->quote = DOUBLE;
	(*i)++;
}

int	change_to_noquote(t_lexer **token, int *i)
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

void	trim_quote(t_lexer **token)
{
	int		len;
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	len = count_len((*token)->str);
	str = (char *)malloc(sizeof(char) * len + 1);
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
		if (inside_quote(tmp->str) && (tmp->prev && tmp->prev->type
				!= LESS_LESS))
			trim_quote(&tmp);
		tmp = tmp->next;
	}
}
