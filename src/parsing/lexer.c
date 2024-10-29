/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ydidenko <ydidenko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/29 14:52:41 by ydidenko      #+#    #+#                 */
/*   Updated: 2024/10/29 14:52:43 by ydidenko      ########   odam.nl         */
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

t_token	*process_tokens(t_token *input)
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

/**
 * @brief This function takes a list of strings and converts it into a list of tokens.
 */
void	lexer(t_list **lst)
{
	t_list	*lst_i;
	t_list	*ret;
	t_token	*token;

	ret = NULL;
	lst_i = *lst;
	while (lst_i != NULL)
	{
		while (1)
		{
			token = (*process_tokens)(lst_i->content);
			if (token == NULL)
				break ;
			ft_lstadd_back(&ret, null_exit(ft_lstnew(token)));
		}
		lst_i = lst_i->next;
	}
	ft_lstclear(lst, ((void (*))(void *)destroy_token));
	*lst = ret;
}
