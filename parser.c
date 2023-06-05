/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandom <aandom@student.abudhabi42.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 19:41:55 by aandom            #+#    #+#             */
/*   Updated: 2023/06/05 21:23:58 by aandom           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int check_token(char *str, int i)
{
	if ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		return (STAB);
	if (str[i] == '|')
		return (PIPE);
	if (str[i] == '>' && str[i + 1] == '>')
		return (GREAT_GREAT);
	if (str[i] == '<' && str[i + 1] == '<')
		return (LESS_LESS);
	if (str[i] == '>')
		return (GREAT);
	if (str[i] == '<')
		return (LESS);
	if (str[i] == '\0')
		return (END);
	else 
		return (0);
	
}

int check_quote(char *str, int i, int  quote)
{
	if (str[i] == '\'' && quote == NONE)
		quote = SINGLE;
	else if (str[i] == '\"' && quote == NONE)
		quote = DOUBLE;
	else if (str[i] == '\'' && quote == SINGLE)
		quote = NONE;
	else if (str[i] == '\"' && quote == DOUBLE)
		quote = NONE;
	return(quote);
}

int extract_word(t_data *data, size_t *i, int start)
{
	int		len;
	int		c;
	char	*word;
	int		tktype;

	len = 0;
	c = 0;
	while(check_token(data->input, *i) == STAB)
		*i = *i + 1;
	tktype = check_token(data->input, *i);
	word = NULL;
	if (!tktype)
	{
		while (check_token(data->input, *i) == 0)
		{
			*i = *i + 1;
			len++;
		}
		*i = *i - len;
		word = malloc(len + 1);
		while (c < len)
		{
			word[c] = data->input[*i];
			*i = *i + 1;
			c++;
		}
	}
	printf ("%s\n", word);
	free(word);
	return (0);
}

void    ft_parser(t_data *data)
{
	size_t i;
	size_t start;
	size_t end;
	int    qtype;

	end = ft_strlen(data->input);
	i = 0;
	qtype = NONE;
	while (i < end)
	{
		qtype = check_quote(data->input, i, qtype);
		if (qtype == NONE)
			start = extract_word(data, &i, start);
		i++;  
	}
}