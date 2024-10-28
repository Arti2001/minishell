/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   token.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: eugenedidenko <eugenedidenko@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/28 20:50:14 by eugenediden   #+#    #+#                 */
/*   Updated: 2024/10/28 21:14:20 by eugenediden   ########   odam.nl         */
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