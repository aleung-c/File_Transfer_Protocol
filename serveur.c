/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serveur.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <aleung-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/27 18:49:52 by aleung-c          #+#    #+#             */
/*   Updated: 2015/05/12 12:07:22 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "serveur.h"

void	read_client(int cs)
{
	int		ret;
	char	buf_client[MSG_BUFSIZE];

	if (cs >= 0)
	{
		ft_putstr(KYEL);
		printf("SUCCESS - Connexion received.\n");
		ft_putstr(RESET);
	}
	while ((ret = read(cs, buf_client, MSG_BUFSIZE - 1)))
	{
		buf_client[ret] = '\0';
		ft_putstr(KGRN);
		ft_putstr("[Received]: ");
		ft_putstr(RESET);
		printf("%d bytes: [%s]\n", ret, buf_client);
		check_input(cs, buf_client);
	}
	exit(0);
}

void	ft_sock_reception(int client_socket)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid >= 0)
	{
		if (child_pid == 0)
			read_client(client_socket);
	}
	else
	{
		ft_putendl_fd("Fork failed", 2);
		exit(-1);
	}
}

int		create_server(int port)
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
	sin.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind(sock, (const struct sockaddr *)&sin, sizeof(sin)) == -1)
	{
		ft_putendl_fd("Bind error.", 2);
		exit (-1);
	}
	ft_putstr(KGRN);
	printf("SUCCESS - Server Created.\n");
	ft_putstr(RESET);
	printf("Port: %d\n", port);
	printf("Server socket: %d\n", sock);
	listen(sock, 42);
	printf("- Awaiting connections... -\n");
	return (sock);
}

int		main(int argc, char **argv)
{
	int					sock;
	int					client_sock;
	unsigned int		cslen;
	struct sockaddr_in	*csin;

	if (argc != 2)
		usage(argv[0]);
	else
	{
		if (check_arg1(argv[1]) != 0)
			return (-1);
		g_home = get_serv_home();
		sock = create_server(ft_atoi(argv[1]));
		while (1)
		{
			client_sock = accept(sock, (struct sockaddr *)&csin, &cslen);
			ft_sock_reception(client_sock);
		}
		close(client_sock);
		close(sock);
	}
	return (0);
}
