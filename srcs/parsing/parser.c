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

#include "../../includes/parse.h"

static int	check_consecutive(t_lexer *token)
{
	if (token->prev)
	{
		if (token->type == PIPE && token->prev->type == PIPE)
			return (1);
		if (token->type >= PIPE && token->prev->type > PIPE)
			return (1);
		if (token->type == END && token->prev->type >= PIPE)
			return (1);
	}
	return (0);
}

static int	parsing_check(t_lexer **token)
{
	t_lexer	*tmp;

	tmp = *token;
	if (tmp && tmp->type == PIPE)
	{
		ft_errmsg(TOK_ERR, "|\'", NOQUOTE);
		return (1);
	}
	while (tmp)
	{
		if (check_consecutive(tmp))
		{
			if (tmp->type == END && tmp->prev && tmp->prev->type > PIPE)
				ft_errmsg(TOK_ERR, "newline\'", NOQUOTE);
			else if (tmp->type == END && tmp->prev)
				ft_errmsg(TOK_ERR, tmp->prev->str, NOQUOTE);
			else
				ft_errmsg(TOK_ERR, tmp->str, NOQUOTE);
			return (1);
		}
		tmp = tmp->next;
	}
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

static int	ft_parser(t_data *data)
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

int	parse_input(t_data *data, t_exno *ex_no)
{
	if (data->input == NULL)
	{
		ft_putendl_fd("", STDERR_FILENO);
		ft_exit(data, NULL, ex_no);
	}
	else if (ft_strcmp(data->input, "\0") == 0)
		return (0);
	add_history(data->input);
	if (ft_parser(data) == 1)
		return (0);
	if (data->lexed->type == END)
		return (0);
	if (parsing_check(&data->lexed) == 1)
		return (0);
	if (ft_expand_var(data, &data->lexed, ex_no) == 0)
		return (0);
	remove_quotes(&data->lexed);
	extract_command(data, data->lexed);
	return (1);
}
