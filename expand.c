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

# include "minishell.h"

void    check_var(t_lexer  **token)
{
    int i;

    i = 0;
    while (*token && (*token)->str && (*token)->str[i])
    {
        if ((*token)->str[i] == '$')
        {
               if ((*token)->prev && (*token)->prev->type == LESS_LESS)
                    break;
                (*token)->is_var = 1;
                return ;
        }
        i++;
    }
}

void    update_quotes(t_lexer **token, char c)
{
    if (c == '\'' && (*token)->quote == NOQUOTE)
        (*token)->quote = SINGLE;
    else if (c == '\"' && (*token)->quote == NOQUOTE)
        (*token)->quote = DOUBLE;
    else if ((c == '\'' && (*token)->quote == SINGLE) || \
             (c == '\"' && (*token)->quote == DOUBLE))
        (*token)->quote = NOQUOTE; 
}

int is_next_char_sep(char *str, int i)
{
    if (str[i] == ' ' || str[i] == '$' || str[i] == '=' || str[i] == '\0')
        return (1);
    return (0);
}

int is_valid_expansion(t_lexer *token, int i)
{
    if (is_next_char_sep(token->str, i + 1))
        return (0);
    if (i > 1 && (token->str[i - 1] == '\"' && token->str[i + 1] == '\"'))
        return (0);
    if (token->quote == SINGLE)
        return (0);
    return (1);
}

int get_var_len(char *str)
{
    int i;
    int count;
    
    i = 0;
    count = 0;
    while (str[i] && str[i] != '$')
        i++;
    i++;
    if (ft_isdigit(str[i]) || str[i] == '?')
        return (count + 1);
    while (str[i])
    {
        if (ft_isalnum(str[i]) || str[i] == '-')
        {
            i++;
            count++;
        }
        else
            break;
    }
    return (count);
}

char    *get_varname(char   *str)
{
    int     start;
    int     len;
    char    *varname;
    
    start = 0;
    while (str[start])
    {
        if (str[start] == '$')
        {
            start = start + 1;
            break;
        }
        start++;
    }
    len = get_var_len(str);
    varname = ft_substr(str, start, len);
    if (!varname)
        return (NULL);
    return (varname);

}

char    *get_varvalue(t_evar *evar, char *key)
{
    char    *varvalue;
    t_evar  *tmp;

    tmp = evar;
    varvalue = NULL;
    while (tmp)
    {
        if(!ft_strncmp(tmp->key, key, ft_strlen(key)))
        {
            varvalue = ft_strdup(tmp->value);
            break;
        }
        tmp = tmp->next;
    }
    return (varvalue);
}

int var_in_env(t_evar *envar, char *key)
{
    while (envar)
    {
        if (!ft_strncmp(envar->key, key, ft_strlen(key)))
            return (1);
        envar = envar->next;
    }
    return (0);
}

char    *extract_var_value(t_lexer *token, int i, t_data *data)
{
    char    *varname;
    char    *varvalue;

    varname = get_varname(token->str + i);
    if (varname && var_in_env(data->envar, varname))
        varvalue = get_varvalue(data->envar, varname);
    else if(varname && varname[0] == '?')
        varvalue = ft_itoa(exit_code);
    else
        varvalue = NULL;
    voidfree(varname);
    return (varvalue);
}


void    delete_var(t_lexer **token, char *str, int index)
{
    char    *newstr;
    int     len;
    int     i;
    int     j;

    i = 0;
    j = 0;
    len = ft_strlen(str) - get_var_len(str + index);
    newstr = malloc (sizeof(char) * (len + 1));
    if (!newstr)
        return ;
    while (str[i])
    {
        if (i == index && str[i] == '$')
        {
            i = i + get_var_len(str + index) + 1;
            if (str[i] == '\0')
                break;
        }
        newstr[j] = str[i];
        i++;
        j++;
    }
    newstr[j] = '\0';
    voidfree((*token)->str);
    (*token)->str = newstr;
    return ;
}

char    *copy_token_str(char *str, char *value, int index, int len)
{
    char *newstr;
    int     i;
    int     j;
    int     m;

    i = 0;
    j = 0;
    m = 0;
    newstr = malloc(sizeof(char) * len + 1);
    if (!newstr)
        return (NULL);
    while(str[i])
    {
        if (i == index && str[i] == '$')
        {
            i = i + get_var_len(str + index) + 1;
            while(value[m])
                newstr[j++] = value[m++];
            if (str[i] == '\0')
                break;
        }
        newstr[j++] = str[i++];
    }
    newstr[j] = '\0';
    return (newstr);
}

void    update_var(t_lexer **token, char *str, int index, char *value)
{
    char    *newstr;
    int     len;

    len = ft_strlen(str) - get_var_len(str + index) + ft_strlen(value);
    newstr = copy_token_str(str, value, index, len);
    free((*token)->str);
    (*token)->str = newstr;
    return ;

}

void    replace_var(t_lexer **token, char *varvalue, int index)
{
    if (varvalue == NULL)
        delete_var(token, (*token)->str, index);
    else
        update_var(token, (*token)->str, index, varvalue);
    voidfree(varvalue);
    return ;
}

int expand_var(t_data *data, t_lexer **token)
{
    int     i;
    t_lexer *tmp;

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
                {
                    replace_var(&tmp, extract_var_value(tmp, i, data), i);
                    // printf("After_replace = [%s]\n", tmp->str);
                }
                else
                    i++;
            }
        }
        tmp = tmp->next;
        
    }
    return (1);
}

int    ft_expand_var(t_data *data, t_lexer **token)
{
    t_lexer *tmp;

    tmp = *token;
    // printf("token = [%s]\n", tmp->str);
    if (tmp && tmp->type == PIPE)
        return(printf("syntax error near unexpected token"), 0);
    while (tmp)
    {
        check_var(&tmp);
        tmp = tmp->next;
    }
    return(expand_var(data, token), 1);
}