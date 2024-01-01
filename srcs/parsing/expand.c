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

#include "../../includes/parse.h"

static void	update_quotes(t_lexer **token, char c)
{
	if (c == '\'' && (*token)->quote == NOQUOTE)
		(*token)->quote = SINGLE;
	else if (c == '\"' && (*token)->quote == NOQUOTE)
		(*token)->quote = DOUBLE;
	else if ((c == '\'' && (*token)->quote == SINGLE)
		|| (c == '\"' && (*token)->quote == DOUBLE))
		(*token)->quote = NOQUOTE;
}

static int	is_valid_expansion(t_lexer *token, int i)
{
	if (!token->str || !token->str[i])
		return (0);
	if (is_next_char_sep(token->str, i + 1) || token->str [i + 1] == '\"'
		|| token->str[i + 1] == '\'')
		return (0);
	if (i > 1 && (token->str[i - 1] == '\"' && token->str[i + 1] == '\"'))
		return (0);
	if (token->quote == SINGLE)
		return (0);
	return (1);
}

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
