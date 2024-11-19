/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amysiv <amysiv@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 17:09:25 by amysiv            #+#    #+#             */
/*   Updated: 2024/11/19 17:03:55 by amysiv           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h>

//g_signal =0;

//handler(){
//	g_signal = 1;
//	printf
//	write
	
//}


//void funv()
//{
//	int i =0;.
//	i =1;
	
//	while (g_signal == 0)
//	{
//		readline {
//			read(0, buf, BUFSIZE);
//		}
//	}
//}


void	 handler(int num)
{
	printf("Printf recieved  %d signal\n", num);
}
//int main()
//{
//	struct sigaction	sa;

//	//sigemtyset()
//	sa.sa_handler = &handler;
//	while (1)
//	{


//		//signal(SIGINT, handler);
//		//printf("Waiting for interupt %d\n", getpid());
//		sleep(1);
//	}
//}


