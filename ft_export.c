/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandom <aandom@student.abudhabi42.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 15:24:24 by tpetros           #+#    #+#             */
/*   Updated: 2023/08/03 16:12:15 by aandom           ###   ########.fr       */
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

void	ft_del_env(t_evar **head, char *str)
{
	t_evar	*temp;
	t_evar	*prev;

    if (!head || !*head || !str)
        return ;
    temp = *head;
	prev = NULL;
    if (temp != NULL && ft_strncmp(temp->key, str, ft_strlen(str)) == 0)
    {
        *head = temp->next;
        free(temp->key);
        free(temp->value);
        free(temp);
        return;
    }
    while (temp != NULL && ft_strncmp(temp->key, str, ft_strlen(str)) != 0)
    {
        prev = temp;
        temp = temp->next;
    }
    if (temp == NULL)
        return ;
    prev->next = temp->next;
    free(temp->key);
    free(temp->value);
    free(temp);
}

int	is_invalid_key(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isalpha(str[i]) || str[i] == '_' || str[i] == '!')
			i++;
		else
			return (0);
	}
	return (i);
}

void	ft_print_export(t_data *data)
{
	char	**tab;
	int		i;

	env_pointer(data);
	sort_env(data->env, ft_envlen(data->envar));
	tab = data->env;
	i = 0;
	while (tab[i])
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putendl_fd(tab[i], 1);
		i++;
	}
}

int	ft_export(t_data *d)
{
	int		i;
	t_evar	*tmp;
	int		code;

	i = 1;
	code = EXIT_SUCCESS;
	if (d->cmds->cmdarg[1] != NULL)
	{
		while (d->cmds->cmdarg[i])
		{
			tmp = new_evar(d->cmds->cmdarg[i]);
			if (is_invalid_key(tmp->key) == 0)
			{
				printf("minishell: export: `%s=%s': not a valid identifier\n",
					tmp->key, tmp->value);
				code = EXIT_FAILURE;
			}
			if (ft_already_exit(d->envar, tmp->key))
				ft_del_env(&d->envar, tmp->key);
			add_back_env(&d->envar, tmp);
			i++;
		}
	}
	else
		ft_print_export(d);
	return (code);
}