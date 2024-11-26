/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   convert_tokens_utils.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ydidenko <ydidenko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/26 15:30:50 by ydidenko      #+#    #+#                 */
/*   Updated: 2024/11/26 16:30:08 by ydidenko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pars_err(t_pars *pars, t_list *lst, char *err_msg)
{
	ft_putstr_fd(err_msg, 2);
	free_pars(pars);
	ft_lstclear(&lst, ((void (*))(void *)destroy_token));
	return (1);
}

int	process_token(t_pars **head, t_pars **current, t_list **token_list,
		t_list *lst)
{
	t_token	*token;

	token = (t_token *)(*token_list)->content;
	if (token->type == PIPE)
	{
		if (process_pipe_token(head, current, lst) != 0)
			return (1);
	}
	else
	{
		if (ensure_current_initialized(head, current, lst) != 0)
			return (1);
		if (is_token_type_redir(*token))
		{
			if (process_redirection_token(*current, token_list, lst,
					*head) != 0)
				return (1);
		}
		else if (is_token_type_text(*token))
		{
			add_cmd_arg(*current, token->str);
		}
	}
	return (0);
}

int	process_pipe_token(t_pars **head, t_pars **current, t_list *lst)
{
	t_pars	*new_pars;

	new_pars = create_new_pars();
	if (!new_pars)
		return (pars_err(*head, lst,
				"Error: failed to create new process\n"));
	if (!*head)
		*head = new_pars;
	else if (*current)
		(*current)->next_process = new_pars;
	*current = new_pars;
	return (0);
}

int	ensure_current_initialized(t_pars **head, t_pars **current, t_list *lst)
{
	if (!*current)
	{
		*current = create_new_pars();
		if (!*current)
			return (pars_err(*head, lst,
					"Error: failed to create new process\n"));
		*head = *current;
	}
	return (0);
}

int	process_redirection_token(t_pars *current, t_list **token_list, t_list *lst,
		t_pars *head)
{
	t_token	*token;
	t_token	*filename_token;

	token = (t_token *)(*token_list)->content;
	if (!(*token_list)->next)
		return (pars_err(head, lst,
				"Error: expected filename after redirection\n"));
	*token_list = (*token_list)->next;
	filename_token = (t_token *)(*token_list)->content;
	if (!is_token_type_text(*filename_token))
		return (pars_err(head, lst,
				"Error: expected filename after redirection\n"));
	add_redirection(current, map_token_to_redirect(token->type),
		filename_token);
	return (0);
}
