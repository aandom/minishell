/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandom <aandom@student.abudhabi42.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 01:26:38 by aandom            #+#    #+#             */
/*   Updated: 2023/08/08 01:26:38 by aandom           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/token.h"

static int	check_token(char *str, int i)
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

static void	add_word_to_lexer(t_data *data, int start, size_t end, int type)
{
	char	*word;
	int		i;

	i = 0;
	word = (char *)malloc(sizeof(char) * (end - start + 1));
	if (!word)
		return ;
	while (start < (int)end)
	{
		word[i] = data->input[start];
		i++;
		start++;
	}
	word[i] = '\0';
	ft_add_token_back(&data->lexed, ft_new_token(word, type));
}

static void	add_token_to_lexer(t_data *data, size_t idx, int type)
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
