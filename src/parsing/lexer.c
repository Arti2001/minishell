/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: eugenedidenko <eugenedidenko@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/28 21:38:29 by eugenediden   #+#    #+#                 */
/*   Updated: 2024/10/28 21:52:48 by eugenediden   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	tokenize_word(char *line, int i, t_token *token)
{
	int	start;

	start = i;
	token->type = DEFAULT;
	while (line[i] && !ft_strchr("<>|\'\"", line[i]) \
			&& !is_whitespace(line[i]))
		i++;
	token->str = null_exit(ft_substr(&line[start], 0, i - start));
	return (i);
}

static int	tokenize_space(char *line, int i, t_token *token)
{
	token->type = SEPERATOR;
	token->str = null_exit(ft_strdup(" "));
	while (is_whitespace(line[i]))
		i++;
	return (i);
}

t_token	*lexer(t_token *input)
{
	t_token		*token;
	static int	i = 0;

	token = init_token();
	if (is_whitespace(input->str[i]))
		i = tokenize_space(input->str, i, token);
	else if (input->str[i] == '\'' || input->str[i] == '\"')
		i = i + tokenize_quoted(input->str, i, token);
	else if (input->str[i] == '<' || input->str[i] == '>' \
			|| input->str[i] == '|')
		i = i + tokenize_sym(input->str, i, token);
	else if (input->str[i])
		i = tokenize_word(input->str, i, token);
	else
	{
		free(token);
		i = 0;
		return (NULL);
	}
	return (token);
}
