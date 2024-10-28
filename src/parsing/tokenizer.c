/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenizer.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: eugenedidenko <eugenedidenko@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/28 20:26:59 by eugenediden   #+#    #+#                 */
/*   Updated: 2024/10/28 21:52:10 by eugenediden   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_list	*tokenizer(char *line)
{
	t_list *tokens;

	tokens = null_exit(ft_lstnew(create_token(line, DEFAULT)));
	update_t_list(&tokens, lexer);
	return (tokens);
}