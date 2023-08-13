/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandom <aandom@student.abudhabi42.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 17:47:46 by aandom            #+#    #+#             */
/*   Updated: 2023/07/26 17:47:46 by aandom           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	repl_var(t_lexer **token, char *varvalue, int index)
{
	if (varvalue == NULL)
		delete_var(token, (*token)->str, index);
	else
		update_var(token, (*token)->str, index, varvalue);
	voidfree(varvalue);
	return ;
}

int	expand_var(t_data *data, t_lexer **token, t_exno *ex_no)
{
	int		i;
	t_lexer	*tmp;

	tmp = *token;
	while (tmp)
	{
		if (tmp->is_var == 1)
		{
			i = 0;
			while (tmp->str[i])
			{
				update_quotes(&tmp, tmp->str[i]);
				if (tmp->str[i] == '$' && is_valid_expansion(tmp, i))
					repl_var(&tmp, ex_var_val(tmp, i, data, ex_no), i);
				else
					i++;
			}
		}
		tmp = tmp->next;
	}
	return (1);
}

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

int	parsing_check(t_lexer **token)
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

int	ft_expand_var(t_data *data, t_lexer **token, t_exno *ex_no)
{
	t_lexer	*tmp;

	tmp = *token;
	while (tmp)
	{
		check_var(&tmp);
		tmp = tmp->next;
	}
	return (expand_var(data, token, ex_no), 1);
}
