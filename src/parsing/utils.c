/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ydidenko <ydidenko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/29 14:53:15 by ydidenko      #+#    #+#                 */
/*   Updated: 2024/11/07 14:41:15 by ydidenko      ########   odam.nl         */
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
