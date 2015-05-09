/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serv_errors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <aleung-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/09 10:20:37 by aleung-c          #+#    #+#             */
/*   Updated: 2015/05/09 14:49:43 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "serveur.h"

int		check_arg1(char *arg)
{
	int port;

	port = ft_atoi(arg);
	if (port > 49151 || port < 1024)
	{
		ft_putstr_fd("Invalid port\n", 2);
		return (-1);
	}
	return (0);
}

void	usage(char *str)
{
	ft_putstr_fd("Usage: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(" [port]\n", 2);
	exit(-1);
}
