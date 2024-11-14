/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   split_tokens.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: ydidenko <ydidenko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/07 17:50:02 by ydidenko      #+#    #+#                 */
/*   Updated: 2024/11/07 17:51:13 by ydidenko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	split_default(t_list **lst, char *str)
{
	size_t	i;
	char	**split;

	i = 0;
	split = null_exit(ft_splitset(str, WHITESPACE));
	if (split[0] == NULL)
	{
		ft_split_free(split);
		return ;
	}
	while (split[i])
	{
		ft_lstadd_back(lst, null_exit(\
		ft_lstnew(create_token(split[i], DEFAULT))));
		if (split[i + 1])
			ft_lstadd_back(lst, null_exit(\
			ft_lstnew(create_token(" ", SEPERATOR))));
		i++;
	}
	ft_split_free(split);
}

/**
 * @brief split default tokens on spaces
 *
 * @param tokens list
 * @return t_list* updated token list
 */
t_list	*split_tokens_f(t_list *tokens)
{
	t_list	*ret;
	t_token	*token;

	ret = NULL;
	while (tokens)
	{
		token = tokens->content;
		if (token->type == DEFAULT)
			split_default(&ret, token->str);
		else
			ft_lstadd_back(&ret, null_exit(\
				ft_lstnew(create_token(token->str, token->type))));
		tokens = tokens->next;
	}
	return (ret);
}

/**
 * @brief split tokens on spaces
 *
 * @param lst list of tokens
 */
void	split_tokens(t_list **lst)
{
	t_list	*ret;

	ret = split_tokens_f(*lst);
	ft_lstclear(lst, free);
	*lst = ret;
}