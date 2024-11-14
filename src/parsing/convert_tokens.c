/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   convert_tokens.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: ydidenko <ydidenko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/07 18:06:00 by ydidenko      #+#    #+#                 */
/*   Updated: 2024/11/14 14:52:42 by ydidenko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_pars *create_new_pars(void)
{
	t_pars *pars = malloc(sizeof(t_pars));
	if (!pars)
		return NULL;
	pars->fd_in = -1;
	pars->fd_out = -1;
	pars->cmd = NULL;
	pars->redir = NULL;
	pars->next_process = NULL;

	return pars;
}

void add_cmd_arg(t_pars *pars, char *arg)
{
	size_t len = 0;
	while (pars->cmd && pars->cmd[len])
		len++;

	char **new_cmd = malloc(sizeof(char *) * (len + 2));
	if (!new_cmd)
		return;

	for (size_t i = 0; i < len; i++)
		new_cmd[i] = pars->cmd[i];

	new_cmd[len] = ft_strdup(arg);
	new_cmd[len + 1] = NULL;

	free(pars->cmd);
	pars->cmd = new_cmd;
}

void add_redirection(t_pars *pars, t_redirect_type redir_type, char *filename)
{
	size_t len = 0;
	size_t i = 0;

	while (pars->redir && pars->redir[len].filename != NULL)
		len++;
	t_redirect *new_redir = malloc(sizeof(t_redirect) * (len + 2));
	if (!new_redir)
		return ;
	while (i < len)
	{
		new_redir[i].type = pars->redir[i].type;
		new_redir[i].filename = pars->redir[i].filename;
		i++;
	}
	new_redir[len].type = redir_type;
	new_redir[len].filename = ft_strdup(filename);
	if (!new_redir[len].filename)
		return (free(new_redir), free(pars->redir));
	new_redir[len + 1].filename = NULL;
	free(pars->redir);
	pars->redir = new_redir;
}

void free_pars(t_pars *pars)
{
	if (!pars)
		return;

	if (pars->cmd)
	{
		for (size_t i = 0; pars->cmd[i]; i++)
			free(pars->cmd[i]);
		free(pars->cmd);
	}

	if (pars->redir)
	{
		while (pars->redir->filename)
		{
			free(pars->redir->filename);
			pars->redir++;
		}
		free(pars->redir);
	}

	free(pars);
}

t_pars	*convert_tokens(t_list *lst)
{
	t_pars	*head;
	t_pars	*current;
	t_list	*token_list;
	t_token	*token;

	head = NULL;
	current = NULL;
	token_list = lst;
	while (token_list)
	{
		token = (t_token *)token_list->content;
		if (token->type == PIPE)
		{
			t_pars *new_pars = create_new_pars();
			if (!new_pars)
				return (free_pars(head), NULL);
			if (!head)
				head = new_pars;
			else if (current)
				current->next_process = new_pars;

			current = new_pars;
		}
		else
		{
			if (!current)
			{
				current = create_new_pars();
				if (!current)
				{
					free_pars(head);
					return NULL;
				}
				head = current;
			}

			if (is_token_type_redir(*token))
			{
				if (!token_list->next)
				{
					// Error: redirection without filename
					free_pars(head);
					return NULL;
				}

				token_list = token_list->next;
				t_token *filename_token = (t_token *)token_list->content;

				if (!is_token_type_text(*filename_token))
				{
					// Error: expected filename after redirection
					free_pars(head);
					return NULL;
				}
				add_redirection(current, map_token_to_redirect(token->type), filename_token->str);
			}
			else if (is_token_type_text(*token))
			{
				add_cmd_arg(current, token->str);
			}
		}
		token_list = token_list->next;
	}
	return (head);
}
