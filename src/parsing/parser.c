/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: amysiv <amysiv@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/29 14:52:30 by ydidenko      #+#    #+#                 */
/*   Updated: 2024/12/01 16:34:14 by ydidenko      ########   odam.nl         */
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
	{
		shell_putendl_fd("Error: failed to convert tokens\n", 2);
		return (NULL);
	}
	//print_pars(pars);
	ft_lstclear(&tokens, ((void (*))(void *)destroy_token));
	return (pars);
}
