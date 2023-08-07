/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandom <aandom@student.abudhabi42.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 19:41:55 by aandom            #+#    #+#             */
/*   Updated: 2023/06/29 21:32:48 by aandom           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_token(char *str, int i)
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

int	check_quote(char *str, int i, int quote)
{
	if (!str)
		return (NOQUOTE);
	if (str[i] == '\'' && quote == NOQUOTE)
		quote = SINGLE;
	else if (str[i] == '\"' && quote == NOQUOTE)
		quote = DOUBLE;
	else if (str[i] == '\'' && quote == SINGLE)
		quote = NOQUOTE;
	else if (str[i] == '\"' && quote == DOUBLE)
		quote = NOQUOTE;
	return (quote);
}

int	ft_parser(t_data *data)
{
	size_t	i;
	size_t	start;
	size_t	end;
	int		qtype;

	end = ft_strlen(data->input);
	i = 0;
	start = 0;
	qtype = NOQUOTE;
	while (i <= end && end > 0)
	{
		qtype = check_quote(data->input, i, qtype);
		if (qtype == NOQUOTE)
			start = extract_word(data, &i, start);
		i++;
	}
	if (qtype != NOQUOTE)
	{
		ft_errmsg(QERRMSG, NULL, qtype);
		ft_errmsg("syntax error: ", "unexpected end of file", NOQUOTE);
		return (1);
	}
	return (0);
}
