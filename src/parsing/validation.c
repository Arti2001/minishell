/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   validation.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: ydidenko <ydidenko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/02 16:24:22 by ydidenko      #+#    #+#                 */
/*   Updated: 2024/12/06 13:23:51 by ydidenko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_consecutive_valid(t_list *tokens)
{
	t_token	*token;

	while (tokens)
	{
		token = tokens->content;
		if (is_token_type_redir(*token))
		{
			if (tokens->next == NULL)
				return (1);
			token = tokens->next->content;
			if (is_token_type_redir(*token))
				return (0);
		}
		if (token->type == PIPE)
		{
			if (tokens->next == NULL)
				return (0);
			token = tokens->next->content;
			if (token->type == PIPE)
				return (0);
		}
		tokens = tokens->next;
	}
	return (1);
}

static int	check_quotes(t_list *tokens)
{
	t_token	*token;

	while (tokens)
	{
		token = tokens->content;
		if (token->type == UNCLOSED)
			return (0);
		tokens = tokens->next;
	}
	return (1);
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
	if (is_consecutive_valid(tokens) == 0 || check_quotes(tokens) == 0)
		return (0);
	return (1);
}
