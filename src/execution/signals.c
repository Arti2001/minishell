/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amysiv <amysiv@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 17:09:25 by amysiv            #+#    #+#             */
/*   Updated: 2024/11/20 16:05:06 by amysiv           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h>




static void	handler(int num)
{
	printf("Printf recieved  %d signal\n", num);
}
void	init_siagtion(void)
{
	struct sigaction	sa;

	sa.sa_handler = &handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	
	if (sigaction(SIGINT, &sa, NULL) == -1)
	{
		perror("Failed to call sigaction().");
		exit(0);
	}
}


