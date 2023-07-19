/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpetros <tpetros@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 15:24:24 by tpetros           #+#    #+#             */
/*   Updated: 2023/07/19 15:24:29 by tpetros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char    *extract_key(char *str)
{
    char    *res;
    size_t  len;

    len = 0;
    while (str[len] && str[len] != '=')
        len++;
    res = ft_substr(str, 0, len);
    return(res);
}

static char    *extract_value(char *str)
{
    char    *res;
    size_t  len;
    size_t  start;

    start = 0;
    while (str[start] && str[start] != '=')
        start++;
    start++;
    len = ft_strlen(str + start);
    res = ft_substr(str, start, len);
    return(res);
}


static t_evar  *new_evar(char  *str)
{
    t_evar  *newvar;

    newvar  = malloc(sizeof(t_evar));
    if(!newvar)
        return (NULL);
    newvar->key = extract_key(str);
    newvar->value = extract_value(str);
    newvar->next = NULL;
    return (newvar);
    
}

static void    add_back_env(t_evar **evar, t_evar *newvar)
{
    t_evar	*tmp;

	tmp = *evar;
	if (tmp == NULL)
	{
		*evar = newvar;
		return ;
	}
	if(evar && *evar && newvar)
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = newvar;
	}
	return ;
}


int	ft_already_exit(t_evar *env, char *str)
{
	t_evar	*tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strncmp(str, tmp->key, ft_strlen(str)) == 0)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

void	ft_del_env(t_evar *env, char *str)
{
    t_evar	*current;
    t_evar	*prev;

	current = env;
    if (current == NULL)
        return ;
    while (current != NULL && ft_strncmp(current->key, str, ft_strlen(current->key)) != 0) {
        prev = current;
        current = current->next;
    }
    if (current == NULL)
        return;
    if (prev == NULL)
        env = current->next;
    else
        prev->next = current->next;
    free(current->key);
	free(current->value);
    free(current);
}

void    ft_export(t_data *d)
{
	int		i;
	t_evar	*tmp;
	t_evar	*tmp2;

	i = 1;
	if (d->cmds->cmdarg[1] != NULL)
	{
		while (d->cmds->cmdarg[i])
		{
			tmp = new_evar(d->cmds->cmdarg[i]);
			if (ft_already_exit(d->envar, tmp->value))
				ft_del_env(d->envar, tmp->key);
			add_back_env(d->envar, tmp);
			i++;
		}
	}
	else
	{
		tmp2 = d->envar;
		while (tmp2)
		{
			printf("declare -x %s=%s\n", tmp2->key, tmp2->value);
			tmp2 = tmp2->next;
		}
	}
}


