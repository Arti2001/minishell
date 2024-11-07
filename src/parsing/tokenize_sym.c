/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenize_sym.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: ydidenko <ydidenko@student.codam.nl          +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/28 21:55:15 by ydidenko      #+#    #+#                 */
/*   Updated: 2024/11/07 14:41:59 by ydidenko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	fill_token(t_type label, const char *sym, \
				t_token *token)
{
	token->type = label;
	token->str = null_exit(ft_strdup(sym));
	return (ft_strlen(sym));
}

size_t	tokenize_sym(char *line, int i, t_token *token)
{
	if (line[i] == '>' && line[i + 1] == '>')
		return (fill_token(REDIR_OUTPUT_APPEND, ">>", token));
	if (line[i] == '<' && line[i + 1] == '<')
		return (fill_token(HEREDOC, "<<", token));
	if (line[i] == '<')
		return (fill_token(REDIR_INPUT, "<", token));
	if (line[i] == '>')
		return (fill_token(REDIR_OUTPUT, ">", token));
	if (line[i] == '|')
		return (fill_token(PIPE, "|", token));
	return (0);
}
