/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serv_display.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <aleung-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/30 16:18:52 by aleung-c          #+#    #+#             */
/*   Updated: 2015/05/09 14:47:37 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "serveur.h"

void write_cs(int cs, char *text, int visible)
{
	char *buf_send;

	buf_send = ft_strdup(text);
	if (visible == 1)
	{
		ft_putstr(KGRN);
		ft_putstr("[Sent]: ");
		ft_putstr(RESET);
		printf("%s\n", buf_send);
	}
	write(cs, buf_send, ft_strlen(buf_send));
	free(buf_send);
}

char *get_serv_home(void)
{
	char *cwd;
	char *buf;

	buf = NULL;
	cwd = getcwd(buf, 4096);
	return (cwd);
}
