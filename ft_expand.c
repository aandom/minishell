/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpetros <tpetros@42abudhabi.student.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 18:27:27 by tpetros           #+#    #+#             */
/*   Updated: 2023/07/21 18:27:28 by tpetros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_strcmp(const char *s1, const char *s2)
 {
 	int	i;
 
 	i = 0;
 	while (s1[i] == s2[i] && s1[i] && s2[i])
 		i++;
 	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
 }


char		*ft_strchr(const char *s, int c)
{
	char	find;
	int		i;

	find = (unsigned char)c;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == find)
			return ((char *)s + i);
		i++;
	}
	if (s[i] == find)
		return ((char *)s + i);
	return (0);
}


void    ft_expand(t_data *data)
{
	t_lexer	*tmp;
    t_evar  *v_tmp;

	tmp = data->lexed;
    v_tmp = data->envar;
	while (tmp)
	{
        if (ft_strchr(tmp->str, '$'))
        {
            while (*(tmp->str) == '$')
                (tmp->str)++;
            while (v_tmp)
            {
                if (ft_strcmp((tmp->str), v_tmp->key) == 0)
                {
                    ft_memset(tmp->str, 0, ft_strlen(tmp->str));
                    ft_strlcpy(tmp->str, v_tmp->value, ft_strlen(v_tmp->value) + 1);
                }
                v_tmp = v_tmp->next;
            }
            v_tmp = data->envar;
        }
        printf("|%s|\n", tmp->str);
		tmp = tmp->next;
	}
}
