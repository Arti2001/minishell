/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amysiv <amysiv@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 14:52:30 by ydidenko          #+#    #+#             */
/*   Updated: 2024/11/14 16:08:29 by amysiv           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_pars	*init_pars(char *line, t_env *env)
{
	t_pars	*pars;
	t_list	*tokens;

	tokens = tokenizer(line, env);
	if (!tokens)
		return (NULL);
	// print_tokens(tokens);
	pars = convert_tokens(tokens);
	if (!pars)
		printf("Error: failed to convert tokens\n");
	//print_pars(pars);
	return (pars);
}