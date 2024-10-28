/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   debug_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: eugenedidenko <eugenedidenko@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/28 21:29:31 by eugenediden   #+#    #+#                 */
/*   Updated: 2024/10/28 21:31:23 by eugenediden   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	fprint_token(void *data)
{
	t_token		*token;
	const char	*type_str[] = {
		[DEFAULT] = "DEFAULT", [SINGLE_QUOTED] = "SINGLE_QUOTED", [DOUBLE_QUOTED] = "DOUBLE_QUOTED",
		[REDIR_INPUT] = "REDIR_INPUT", [HEREDOC] = "HEREDOC", [REDIR_OUTPUT] = "REDIR_OUTPUT",
		[REDIR_OUTPUT_APPEND] = "REDIR_OUTPUT_APPEND", [PIPE] = "PIPE", [SEPERATOR] = "SEPERATOR",
		[UNCLOSED] = "UNCLOSED QUOTE",
	};

	token = data;
	ft_printf("type = %s | str = '%s'\n", type_str[token->type], token->str);
}

void	print_tokens(t_list *tokens)
{
	ft_lstiter(tokens, fprint_token);
}
