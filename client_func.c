/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <aleung-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/07 12:02:35 by aleung-c          #+#    #+#             */
/*   Updated: 2015/05/07 13:33:17 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "serveur.h"

void write_sock(int sock,  char *text, int visible)
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
		write(sock, buf_send, ft_strlen(buf_send));
		free(buf_send);
}