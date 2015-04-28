/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serv_get.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <aleung-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/28 17:18:00 by aleung-c          #+#    #+#             */
/*   Updated: 2015/04/28 17:48:14 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "serveur.h"

void go_get(int cs, char **input)
{
	char *buf_send;
	int fd;

	if (!input[1])
	{
		buf_send = ft_strdup("Missing argument to get");
		ft_putstr(KGRN);
		ft_putstr("[Sent]: ");
		ft_putstr(RESET);
		printf("%s\n", buf_send);
		write(cs, buf_send, ft_strlen(buf_send));
	}
	else
	{
		buf_send = ft_strjoin("SUCCESS - getting", input[1]);
		ft_putstr(KGRN);
		ft_putstr("[Sent]: ");
		ft_putstr(RESET);
		printf("%s\n", buf_send);
		write(cs, buf_send, ft_strlen(buf_send));
		if ((fd = open(input[1], O_RDONLY)) < 0)
		{
			buf_send =  ft_strdup("SUCCESS - ERROR - File not existing");
			ft_putstr(KGRN);
			ft_putstr("[Sent]: ");
			ft_putstr(RESET);
			printf("%s\n", buf_send);
			write(cs, buf_send, ft_strlen(buf_send));	
		}


	}

}