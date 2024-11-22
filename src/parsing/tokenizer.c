/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenizer.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ydidenko <ydidenko@student.codam.nl          +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/28 20:26:59 by ydidenko      #+#    #+#                 */
/*   Updated: 2024/11/22 17:44:51 by ydidenko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*tokenizer(char *line, t_i_env *i_env)
{
	t_list	*tokens;

	tokens = null_exit(ft_lstnew(create_token(line, DEFAULT)));
	lexer(&tokens);
	expand_vars(&tokens, i_env);
	split_tokens(&tokens);
	combine_tokens(&tokens);
	return (tokens);
}
