/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: amysiv <amysiv@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/29 14:52:30 by ydidenko      #+#    #+#                 */
/*   Updated: 2024/11/22 17:42:01 by ydidenko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_pars	*init_pars(char *line, t_i_env *i_env)
{
	t_pars	*pars;
	t_list	*tokens;

	tokens = tokenizer(line, i_env);
	if (!tokens)
		return (NULL);
	// print_tokens(tokens);
	pars = convert_tokens(tokens);
	if (!pars)
		printf("Error: failed to convert tokens\n");
	//print_pars(pars);
	return (pars);
}