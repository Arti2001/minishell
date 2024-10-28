/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: eugenedidenko <eugenedidenko@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/28 20:12:10 by eugenediden   #+#    #+#                 */
/*   Updated: 2024/10/28 21:14:14 by eugenediden   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_pars	*init_pars(char *line)
{
	t_pars	*pars;
	t_list	*tokens;

	tokens = lexer(line);
	if (!tokens)
		return (NULL);
	print_tokens(tokens);
	pars = (t_pars *)malloc(sizeof(t_pars));
	if (!pars)
		return (NULL);

	return (pars);
}