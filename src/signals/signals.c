/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amysiv <amysiv@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 17:09:25 by amysiv            #+#    #+#             */
/*   Updated: 2024/12/03 19:40:25 by amysiv           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_sigaction_interactive(void)
{
	struct sigaction sa;
	
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sa.sa_handler = &handler_int;
	if (sigaction(SIGINT, &sa, NULL) == -1)
	{
		perror("Failed to set up SIGINT handler for interactive mode");
		exit(EXIT_FAILURE);
	}
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
	{
		perror("Failed to ignore SIGQUIT in interactive mode");
		exit(EXIT_FAILURE);
	}
}

static void	init_sigaction_non_interactive(void)
{
	struct sigaction sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sa.sa_handler = &handler_non_int;
	if (sigaction(SIGINT, &sa, NULL) == -1)
	{
		perror("Failed to set up SIGINT handler for non-interactive mode");
		exit(EXIT_FAILURE);
	}
	if (signal(SIGQUIT, handler_sigq) == SIG_ERR)
	{
		perror("Failed to set up SIGQUIT handler in non-interactive mode");
		exit(EXIT_FAILURE);
	}
}

static void	init_sigaction_heredoc(void)
{
	struct sigaction sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sa.sa_handler = &handler_heredoc;
	if (sigaction(SIGINT, &sa, NULL) == -1)
	{
		perror("Failed to set up SIGINT handler for heredoc");
		exit(EXIT_FAILURE);
	}
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
	{
		perror("Failed to ignore SIGQUIT in heredoc");
		exit(EXIT_FAILURE);
	}
}

void init_sigaction(int param)
{
	if (param == INTERACTIVE)
	{
		init_sigaction_interactive();
	}
	else if (param == NON_INTERACTIVE)
	{
		init_sigaction_non_interactive();
	}
	else if (param == HEREDOC_SIG)
	{
		init_sigaction_heredoc();
	}
	else
	{
		shell_putendl_fd("Invalid parameter for init_sigaction", 2);
		exit(EXIT_FAILURE);
	}
}


