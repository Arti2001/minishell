/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: amysiv <amysiv@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/29 14:52:30 by ydidenko      #+#    #+#                 */
/*   Updated: 2024/12/06 13:17:51 by ydidenko      ########   odam.nl         */
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
	if (is_valid_tokens(tokens) == 0)
	{
		ft_lstclear(&tokens, ((void (*))(void *)destroy_token));
		i_env->err_code = 2;
		ft_putendl_fd("minishell: syntax error", 2);
		return (NULL);
	}
	pars = convert_tokens(tokens, i_env);
	if (!pars)
		return (NULL);
	ft_lstclear(&tokens, ((void (*))(void *)destroy_token));
	return (pars);
}

void	destroy_tokens(t_list *tokens)
{
	ft_lstclear(&tokens, ((void (*))(void *)destroy_token));
}
