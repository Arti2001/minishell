/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenizer.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ydidenko <ydidenko@student.codam.nl          +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/28 20:26:59 by ydidenko      #+#    #+#                 */
/*   Updated: 2024/10/29 14:51:44 by ydidenko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_list	*tokenizer(char *line)
{
	t_list *tokens;

	tokens = null_exit(ft_lstnew(create_token(line, DEFAULT)));
	lexer(&tokens);
	return (tokens);
}
