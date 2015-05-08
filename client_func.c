/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <aleung-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/07 12:02:35 by aleung-c          #+#    #+#             */
/*   Updated: 2015/05/08 17:47:04 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "serveur.h"

void	write_sock(int sock, char *text, int visible)
{
	char *buf_send;

	buf_send = ft_strdup(text);
	if (visible == 1)
	{
		ft_putstr(KYEL);
		ft_putstr("[Sent]: ");
		ft_putstr(RESET);
		printf("%s\n", buf_send);
	}
	write(sock, buf_send, ft_strlen(buf_send));
	free(buf_send);
}

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

void	prompt(void)
{
	ft_putstr(KYEL);
	ft_putstr("~ Client $> ");
	ft_putstr(RESET);
}

void	display_input(char *buf)
{
	ft_putstr(KYEL);
	ft_putstr("Input: ");
	ft_putstr(RESET);
	printf("[%s]\n", buf);
}
