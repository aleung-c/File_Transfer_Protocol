/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serv_input_parsing.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <aleung-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/01 13:46:25 by aleung-c          #+#    #+#             */
/*   Updated: 2015/04/01 15:00:16 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "serveur.h"

char	*clean_line(char *line)
{
	int i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\t')
			line[i] = ' ';
		i++;
	}
	return (line);
}

char	**get_input(char *buf_client)
{
	char **input;

	buf_client = clean_line(buf_client);
	input = ft_strsplit(buf_client, ' ');
	if (!input)
		ft_putendl_fd("Input recup failed", 2);
	return (input);
}

void check_input(int cs, char *buf_client)
{
	char *buf_send;
	char **input;

	input =  get_input(buf_client);
	if (!(input) || !(input[0]))
		return ;
	else if (ft_strcmp(input[0], "hello") == 0)
	{
		if (!(buf_send = (char *)malloc(sizeof(char) * 1024 + 1)))
			exit(-1);
		buf_send = ft_strdup("how are you?");
		ft_putstr(KGRN);
		ft_putstr("[Sent]: ");
		ft_putstr(RESET);
		printf("how are you?\n");
		write(cs, buf_send, ft_strlen(buf_send)); // send data to client.
	}
	else if (ft_strcmp(input[0], "ls") == 0)
	{
		if (!(buf_send = (char *)malloc(sizeof(char) * 1024 + 1)))
			exit(-1);
		buf_send = ft_strdup("Go ls");
		ft_putstr(KGRN);
		ft_putstr("[Sent]: ");
		ft_putstr(RESET);
		printf("Go ls\n");
		write(cs, buf_send, ft_strlen(buf_send));
	}
	else if (ft_strcmp(input[0], "cd") == 0)
	{
		if (!(buf_send = (char *)malloc(sizeof(char) * 1024 + 1)))
			exit(-1);
		buf_send = ft_strdup("Go cd");
		ft_putstr(KGRN);
		ft_putstr("[Sent]: ");
		ft_putstr(RESET);
		printf("Go cd\n");
		write(cs, buf_send, ft_strlen(buf_send));
	}
	else if (ft_strcmp(input[0], "get") == 0)
	{
		if (!(buf_send = (char *)malloc(sizeof(char) * 1024 + 1)))
			exit(-1);
		buf_send = ft_strdup("Go get");
		ft_putstr(KGRN);
		ft_putstr("[Sent]: ");
		ft_putstr(RESET);
		printf("Go get\n");
		write(cs, buf_send, ft_strlen(buf_send));
	}
	else if (ft_strcmp(input[0], "put") == 0)
	{
		if (!(buf_send = (char *)malloc(sizeof(char) * 1024 + 1)))
			exit(-1);
		buf_send = ft_strdup("Go put");
		ft_putstr(KGRN);
		ft_putstr("[Sent]: ");
		ft_putstr(RESET);
		printf("Go put\n");
		write(cs, buf_send, ft_strlen(buf_send));
	}
	else if (ft_strcmp(input[0], "pwd") == 0)
	{
		if (!(buf_send = (char *)malloc(sizeof(char) * 1024 + 1)))
			exit(-1);
		buf_send = ft_strdup("Go pwd");
		ft_putstr(KGRN);
		ft_putstr("[Sent]: ");
		ft_putstr(RESET);
		printf("Go pwd\n");
		write(cs, buf_send, ft_strlen(buf_send));
	}
	else if (ft_strcmp(input[0], "quit") == 0)
	{
		if (!(buf_send = (char *)malloc(sizeof(char) * 1024 + 1)))
			exit(-1);
		buf_send = ft_strdup("Quiting server ...");
		ft_putstr(KGRN);
		ft_putstr("[Sent]: ");
		ft_putstr(RESET);
		printf("Quiting server ...\n");
		write(cs, buf_send, ft_strlen(buf_send));
		close(cs);
		exit(0);
	}
	else
	{
		buf_send = ft_strdup("No command found.");
		ft_putstr(KGRN);
		ft_putstr("[Sent]: ");
		ft_putstr(RESET);
		printf("%s\n", buf_send);
		write(cs, buf_send, ft_strlen(buf_send)); // send data to client.
	}
}