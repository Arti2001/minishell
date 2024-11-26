/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   convert_tokens.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: amysiv <amysiv@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/07 18:06:00 by ydidenko      #+#    #+#                 */
/*   Updated: 2024/11/26 15:52:46 by ydidenko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_pars	*create_new_pars(void)
{
	t_pars	*pars;

	pars = malloc(sizeof(t_pars));
	if (!pars)
		return (NULL);
	pars->fd_in = STDIN_FILENO;
	pars->cmd = NULL;
	pars->redir = NULL;
	pars->next_process = NULL;
	return (pars);
}

void	add_cmd_arg(t_pars *pars, char *arg)
{
	size_t	len;
	size_t	i;
	char	**new_cmd;

	len = 0;
	i = 0;
	while (pars->cmd && pars->cmd[len])
		len++;
	new_cmd = malloc(sizeof(char *) * (len + 2));
	if (!new_cmd)
		return ;
	while (i < len)
	{
		new_cmd[i] = pars->cmd[i];
		i++;
	}
	new_cmd[len] = ft_strdup(arg);
	new_cmd[len + 1] = NULL;
	free(pars->cmd);
	pars->cmd = new_cmd;
}

void	add_redirection(t_pars *pars, t_redirect_type redir_type,
	t_token *filename)
{
	size_t		len;
	size_t		i;
	t_redirect	*new_redir;

	i = 0;
	len = 0;
	while (pars->redir && pars->redir[len].filename != NULL)
		len++;
	new_redir = malloc(sizeof(t_redirect) * (len + 2));
	if (!new_redir)
		return ;
	while (i < len)
	{
		new_redir[i].type = pars->redir[i].type;
		new_redir[i].filename = pars->redir[i].filename;
		i++;
	}
	new_redir[len].type = redir_type;
	new_redir[len].filename = ft_strdup(filename->str);
	new_redir[len].is_expandable = is_expandable(*filename);
	if (!new_redir[len].filename)
		return (free(new_redir), free(pars->redir));
	new_redir[len + 1].filename = NULL;
	free(pars->redir);
	pars->redir = new_redir;
}

void	free_pars(t_pars *pars)
{
	int	i;

	i = 0;
	if (!pars)
		return ;
	if (pars->cmd)
	{
		while (pars->cmd[i])
			(free(pars->cmd[i]), i++);
		free(pars->cmd);
	}
	if (pars->redir)
	{
		while (pars->redir->filename)
			(free(pars->redir->filename), pars->redir++);
		free(pars->redir);
	}
	if (pars->path)
		free(pars->path);
	if (pars->next_process)
		free_pars(pars->next_process);
	free(pars);
}

void	clean_exit(t_pars *pars, t_list *lst, char *err_msg)
{
	ft_putstr_fd(err_msg, 2);
	free_pars(pars);
	ft_lstclear(lst, ((void (*))(void *)destroy_token));
	exit(1);
}

t_pars	*convert_tokens(t_list *lst)
{
	t_pars	*head;
	t_pars	*current;
	t_list	*token_list;
	t_token	*token;
	t_pars	*new_pars;
	t_token	*filename_token;

	head = NULL;
	current = NULL;
	new_pars = NULL;
	token_list = lst;
	while (token_list)
	{
		token = (t_token *)token_list->content;
		if (token->type == PIPE)
		{
			new_pars = create_new_pars();
			if (!new_pars)
				clean_exit(head, lst, "Error: failed to create new process\n");
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
					clean_exit(head, lst,
						"Error: failed to create new process\n");
				head = current;
			}
			if (is_token_type_redir(*token))
			{
				if (!token_list->next)
					clean_exit(head, lst,
						"Error: expected filename after redirection\n");
				token_list = token_list->next;
				filename_token = (t_token *)token_list->content;
				if (!is_token_type_text(*filename_token))
					clean_exit(head, lst,
						"Error: expected filename after redirection\n");
				add_redirection(current, map_token_to_redirect(token->type),
					filename_token);
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
