/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpetros <tpetros@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 22:21:56 by tpetros           #+#    #+#             */
/*   Updated: 2023/08/08 22:23:08 by tpetros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_evar	*find_evar(t_evar *env, char *key)
{
	t_evar	*tmp;

	tmp = env;
	while (tmp != NULL)
	{
		if (tmp->key && strcmp(tmp->key, key) == 0)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

// void	ft_expanding_tilda(t_data *data)
// {
// 	t_evar	*tmp;
// 	char	*h;
// 	char	*temp;

// 	tmp = data->envar;
// 	h = NULL;
// 	while (tmp)
// 	{
// 		if (tmp->key && ft_strcmp("HOME", tmp->key) == 0)
// 		{
// 			temp = ft_strtrim(data->cmds->cmdarg[1], "~");
// 			h = ft_strjoin(ft_strdup(tmp->value), temp);
// 		}
// 		tmp = tmp->next;
// 	}
// 	if (h)
// 	{
// 		if (chdir(h) != 0)
// 			perror("minishell: cd");
// 	}
// 	free(h);
// 	free(temp);
// }
