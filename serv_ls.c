/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serv_ls.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <aleung-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/02 13:19:55 by aleung-c          #+#    #+#             */
/*   Updated: 2015/05/06 18:24:00 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "serveur.h"

void	go_ls(int cs, char **input) // SEGFAULT.
{
	pid_t child;
	char *buf_send;

	buf_send = ft_strdup("SUCCESS - Go ls");
	ft_putstr(KGRN);
	ft_putstr("[Sent]: ");
	ft_putstr(RESET);
	printf("%s\n", buf_send);
	write(cs, buf_send, ft_strlen(buf_send));


	child = fork();
	if (child == 0)
	{
		dup2(cs, 1);
		execv("/bin/ls", input);
	}
	else
		wait(NULL);
}