/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandom <aandom@student.abudhabi42.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 02:01:19 by aandom            #+#    #+#             */
/*   Updated: 2023/08/08 02:01:19 by aandom           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
