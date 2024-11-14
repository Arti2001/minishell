/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ydidenko <ydidenko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/29 14:53:15 by ydidenko      #+#    #+#                 */
/*   Updated: 2024/11/14 13:14:28 by ydidenko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r');
}

int	is_token_type_redir(t_token token)
{
	if (token.type == REDIR_INPUT || token.type == REDIR_OUTPUT || \
	token.type == REDIR_OUTPUT_APPEND || token.type == HEREDOC)
		return (1);
	return (0);
}

int	is_token_type_text(t_token token)
{
	if (token.type == DEFAULT || token.type == SINGLE_QUOTED || \
	token.type == DOUBLE_QUOTED)
		return (1);
	return (0);
}

t_redirect_type	map_token_to_redirect(t_type type)
{
	static const t_redirect_type	map[10] = {
		[REDIR_INPUT] = IN,
		[REDIR_OUTPUT] = OUT,
		[REDIR_OUTPUT_APPEND] = OUT_A,
		[HEREDOC] = HEREDOC_RE,
	};

	return (map[type]);
}
