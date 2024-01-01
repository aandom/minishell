/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandom <aandom@student.abudhabi42.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 17:06:34 by aandom            #+#    #+#             */
/*   Updated: 2024/01/01 17:06:34 by aandom           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# include "minishell.h"

// ft_token_utils.c
void		ft_add_token_back(t_lexer **tokens, t_lexer *new);
t_lexer		*ft_new_token(char *word, int type);

// ft_token.c
int			extract_word(t_data *data, size_t *i, int start);

#endif