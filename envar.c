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

char	*extract_key(char *str, int *i)
{
	char	*res;
	size_t	len;

	len = 0;
	while (str[len] && str[len] != '=')
		len++;
	if (str[len] == '=')
		*i = 1;
	res = ft_substr(str, 0, len);
	return (res);
}

char	*extract_value(char *str)
{
	char	*res;
	size_t	len;
	size_t	start;

	start = 0;
	while (str[start] && str[start] != '=')
		start++;
	len = ft_strlen(str + start);
	start++;
	res = ft_substr(str, start, len);
	return (res);
}

void	add_back_env(t_evar **evar, t_evar *newvar)
{
	t_evar	*tmp;

	tmp = *evar;
	if (tmp == NULL)
	{
		*evar = newvar;
		return ;
	}
	if (evar && *evar && newvar)
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = newvar;
	}
	return ;
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
		ft_var_freer(temp);
		return ;
	}
	while (temp != NULL && ft_strncmp(temp->key, str, ft_strlen(str)) != 0)
	{
		prev = temp;
		temp = temp->next;
	}
	if (temp == NULL)
		return ;
	prev->next = temp->next;
	ft_var_freer(temp);
}

int	initialize_envar(t_data *data, char **env)
{
	int		i;

	data->env = (char **)malloc(sizeof(char *) * (env_var_len(env) + 1));
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
	data->env[i] = NULL;
	return (1);
}
