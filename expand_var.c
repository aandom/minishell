/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandom <aandom@student.abudhabi42.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 23:00:18 by aandom            #+#    #+#             */
/*   Updated: 2023/08/07 23:00:18 by aandom           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_var(t_lexer **token)
{
	int	i;

	i = 0;
	while (*token && (*token)->str && (*token)->str[i])
	{
		if ((*token)->str[i] == '$')
		{
			if ((*token)->prev && (*token)->prev->type == LESS_LESS)
				break ;
			(*token)->is_var = 1;
			return ;
		}
		i++;
	}
}

char	*get_varvalue(t_evar *evar, char *key)
{
	char	*varvalue;
	t_evar	*tmp;

	tmp = evar;
	varvalue = NULL;
	while (tmp)
	{
		if (!ft_strncmp(tmp->key, key, ft_strlen(key)))
		{
			varvalue = ft_strdup(tmp->value);
			break ;
		}
		tmp = tmp->next;
	}
	return (varvalue);
}

int	var_in_env(t_evar *envar, char *key)
{
	while (envar)
	{
		if (!ft_strncmp(envar->key, key, ft_strlen(key)))
			return (1);
		envar = envar->next;
	}
	return (0);
}

char	*ex_var_val(t_lexer *token, int i, t_data *data, t_exno *ex_no)
{
	char	*varname;
	char	*varvalue;

	varname = get_varname(token->str + i);
	if (varname && var_in_env(data->envar, varname))
		varvalue = get_varvalue(data->envar, varname);
	else if (varname && varname[0] == '?')
		varvalue = ft_itoa(ex_no->exno);
	else
		varvalue = NULL;
	voidfree(varname);
	return (varvalue);
}

void	delete_var(t_lexer **token, char *str, int index)
{
	char	*new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new = malloc (sizeof(char) * (ft_strlen(str) - var_len(str + index) + 1));
	if (!new)
		return ;
	while (str[i])
	{
		if (i == index && str[i] == '$')
		{
			i = i + var_len(str + index) + 1;
			if (str[i] == '\0')
				break ;
		}
		new[j] = str[i];
		i++;
		j++;
	}
	new[j] = '\0';
	voidfree((*token)->str);
	(*token)->str = new;
	return ;
}
