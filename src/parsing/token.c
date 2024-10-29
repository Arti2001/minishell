/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   token.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ydidenko <ydidenko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/29 14:52:56 by ydidenko      #+#    #+#                 */
/*   Updated: 2024/10/29 14:52:57 by ydidenko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*init_token(void)
{
	t_token	*ret;

	ret = null_exit(malloc(sizeof(t_token)));
	ret->str = NULL;
	ret->type = DEFAULT;
	return (ret);
}

t_token	*destroy_token(t_token *token)
{
	free(token->str);
	free(token);
	return (NULL);
}

t_token	*create_token(char *str, t_type type)
{
	t_token	*token;

	token = init_token();
	token->type = type;
	if (str == NULL)
		token->str = NULL;
	else
		token->str = null_exit(ft_strdup(str));
	return (token);
}

void	repalce_t_list(t_list **lst, t_list *(*list_f)(t_list *))
{
	t_list	*tmp;

	tmp = list_f(*lst);
	ft_lstclear(lst, ((void (*))(void *)destroy_token));
	*lst = tmp;
}
