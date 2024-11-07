/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenizer.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ydidenko <ydidenko@student.codam.nl          +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/28 20:26:59 by ydidenko      #+#    #+#                 */
/*   Updated: 2024/11/07 14:29:24 by ydidenko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*tokenizer(char *line, t_env *env)
{
	t_list *tokens;

	tokens = null_exit(ft_lstnew(create_token(line, DEFAULT)));
	lexer(&tokens);
	expand_vars(&tokens, env);
	return (tokens);
}
