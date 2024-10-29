/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ydidenko <ydidenko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/29 14:52:30 by ydidenko      #+#    #+#                 */
/*   Updated: 2024/10/29 14:52:33 by ydidenko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_pars	*init_pars(char *line)
{
	t_pars	*pars;
	t_list	*tokens;

	tokens = tokenizer(line);
	if (!tokens)
		return (NULL);
	print_tokens(tokens);
	pars = (t_pars *)malloc(sizeof(t_pars));
	if (!pars)
		return (NULL);

	return (pars);
}