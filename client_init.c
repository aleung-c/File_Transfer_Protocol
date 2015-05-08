/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <aleung-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/08 17:30:00 by aleung-c          #+#    #+#             */
/*   Updated: 2015/05/08 17:47:45 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "serveur.h"

int create_client(char *addr, int port)
{
	int					sock;
	struct protoent		*proto;
	struct sockaddr_in	sin;

	proto = getprotobyname("tcp");
	if (!proto)
		return (-1);
	sock = socket(PF_INET, SOCK_STREAM, proto->p_proto);
	sin.sin_family = AF_INET;
	sin.sin_port = htons(port);
	sin.sin_addr.s_addr = inet_addr(addr);
	if (connect(sock, (const struct sockaddr *)&sin, sizeof(sin)) == -1)
	{
		ft_putendl_fd("Connect error.", 2);
		exit (-1);
	}
	printf("SUCCESS - Connected to server.\n");
	printf("Port: %d\n", port);
	printf("Client socket: %d\n", sock);
	return (sock);
}
