/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envar.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandom <aandom@student.abudhabi42.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 20:11:12 by aandom            #+#    #+#             */
/*   Updated: 2023/07/18 20:11:12 by aandom           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static t_evar  *get_last_var(t_evar *evar)
{
    while (evar->next != NULL)
		evar = evar->next;
	return (evar);
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

void    copy_env(t_data *data, char **env)
{
    int     i;

    i = 0;
    while(env[i])
    {
        add_back_env(&data->envar, new_evar(env[i]));
        i++;
    }
}

int	env_var_len(char **env)
{
	int	i;

	i = 0;
	while (env && env[i])
		i++;
	return (i);
}

int initialize_envar(t_data *data, char **env)
{
	int		i;

	data->env = malloc( sizeof(char *) * (env_var_len(env) + 1));
	if (!data->env)
		return (0);
	i = 0;
	while (env[i])
	{
		data->env[i] = ft_strdup(env[i]);
		if (!data->env[i])
			return (0);
		i++;
	}
	return (1);
}