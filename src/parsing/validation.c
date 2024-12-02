/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   validation.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: ydidenko <ydidenko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/02 16:24:22 by ydidenko      #+#    #+#                 */
/*   Updated: 2024/12/02 17:17:02 by ydidenko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_consecutive_valid(t_list *tokens)
{
	t_token	*token;

	while (tokens->next)
	{
		token = tokens->content;
		if (is_token_type_redir(*token))
		{
			token = tokens->next->content;
			if (is_token_type_redir(*token))
				return (0);
		}
		if (token->type == PIPE)
		{
			token = tokens->next->content;
			if (token->type == PIPE)
				return (0);
		}
		tokens = tokens->next;
	}
}

int	is_valid_tokens(t_list *tokens)
{
	t_token	*token;

	token = tokens->content;
	if (token->type == PIPE)
		return (0);
	if (ft_lstsize(tokens) == 1)
	{
		if (is_token_type_redir(*token) && token->type != REDIR_INPUT)
			return (0);
	}
	if (is_consecutive_valid(tokens) == 0)
		return (0);
	return (1);
}
