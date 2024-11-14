/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   debug_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: ydidenko <ydidenko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/29 14:52:48 by ydidenko      #+#    #+#                 */
/*   Updated: 2024/11/14 13:33:50 by ydidenko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	fprint_token(void *data)
{
	t_token		*token;
	const char	*type_str[] = {
	[DEFAULT] = "DEFAULT", [SINGLE_QUOTED] = "SINGLE_QUOTED",
	[DOUBLE_QUOTED] = "DOUBLE_QUOTED", [REDIR_INPUT] = "REDIR_INPUT",
	[HEREDOC] = "HEREDOC", [REDIR_OUTPUT] = "REDIR_OUTPUT",
	[REDIR_OUTPUT_APPEND] = "REDIR_OUTPUT_APPEND", [PIPE] = "PIPE",
	[SEPERATOR] = "SEPERATOR", [UNCLOSED] = "UNCLOSED QUOTE",
	};

	token = data;
	ft_printf("type = %s | str = '%s'\n", type_str[token->type], token->str);
}

void	print_tokens(t_list *tokens)
{
	ft_lstiter(tokens, fprint_token);
}

const char *redirect_type_to_string(t_redirect_type type)
{
	switch (type)
	{
		case HEREDOC_RE:
			return "HEREDOC_RE";
		case IN:
			return "IN";
		case OUT:
			return "OUT";
		case OUT_A:
			return "OUT_A";
		default:
			return "UNKNOWN";
	}
}

// Function to print the t_pars structure
void print_pars(t_pars *pars)
{
	int process_num = 1;
	t_pars *current = pars;

	while (current)
	{
		printf("Process %d:\n", process_num);
		// Print command arguments
		if (current->cmd)
		{
			printf("  Command: ");
			for (size_t i = 0; current->cmd[i]; i++)
			{
				printf("%s", current->cmd[i]);
				if (current->cmd[i + 1])
					printf(" ");
			}
			printf("\n");
		}
		else
		{
			printf("  Command: (none)\n");
		}

		// Print redirections
		if (current->redir)
		{
			printf("  Redirections:\n");
			while (current->redir->filename)
			{
				printf("    Type: %s, Filename: %s\n",
					   redirect_type_to_string(current->redir->type),
					   current->redir->filename);
				current->redir++;
			}
		}
		else
		{
			printf("  Redirections: (none)\n");
		}

		// Print file descriptors (if relevant)
		printf("  tmp_read: %d\n", current->tmp_read);
		printf("  fd_in: %d\n", current->fd_in);
		printf("  fd_out: %d\n", current->fd_out);

		printf("\n");

		current = current->next_process;
		process_num++;
	}
}
