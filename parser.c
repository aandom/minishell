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

t_lexer	*ft_new_token(char *word, int type)
{
	t_lexer	*new;

	new = (t_lexer *)malloc(sizeof(t_lexer));
	if (!new)
		return (NULL);
	new->str = word;
	new->next = NULL;
	new->prev = NULL;
	new->type = type;
	new->is_var = 0;
	new->quote = NOQUOTE;
	return (new);
}

void	ft_add_token_back(t_lexer **tokens, t_lexer *new)
{
	t_lexer	*tmp;

	tmp = *tokens;
	if (tmp == NULL)
	{
		*tokens = new;
		return ;
	}
	if (tokens && *tokens && new)
	{
		while (tmp->next != 0)
			tmp = tmp->next;
		tmp->next = new;
		new->prev = tmp;
	}
	return ;
}

void	add_word_to_lexer(t_data *data, int start, size_t end, int type)
{
	char	*word;
	int		i;

	i = 0;
	word = (char *)malloc(sizeof(char) * (end - start + 1));
	if (!word)
		return ;
	while (start < end)
	{
		word[i] = data->input[start];
		i++;
		start++;
	}
	word[i] = '\0';
	ft_add_token_back(&data->lexed, ft_new_token(word, type));
}

void	add_token_to_lexer(t_data *data, size_t idx, int type)
{
	char	*word;
	int		i;
	int		end;

	i = 0;
	end = 2;
	if (type == GREAT_GREAT || type == LESS_LESS)
	{
		word = (char *)malloc (sizeof(char) * 3);
		end = 3;
	}
	else
		word = malloc (sizeof(char) * 2);
	if (!word)
		return ;
	while (i < end - 1)
	{
		word[i] = data->input[idx];
		i++;
		idx++;
	}
	word[i] = '\0';
	ft_add_token_back(&data->lexed, ft_new_token(word, type));
}

int	extract_word(t_data *data, size_t *i, int start)
{
	int		tktype;

	tktype = check_token(data->input, (*i));
	if (tktype != 0)
	{
		if ((*i) != 0 && check_token(data->input, (*i) - 1) == 0)
			add_word_to_lexer(data, start, (*i), WORD);
		if (tktype == PIPE || tktype == GREAT || tktype == GREAT_GREAT
			|| tktype == LESS || tktype == LESS_LESS || tktype == END)
		{
			add_token_to_lexer(data, (*i), tktype);
			if (tktype == GREAT_GREAT || tktype == LESS_LESS)
				(*i) = (*i) + 1;
		}
		start = (*i) + 1;
	}
	return (start);
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
