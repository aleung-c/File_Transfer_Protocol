/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <aleung-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/08 17:30:31 by aleung-c          #+#    #+#             */
/*   Updated: 2015/05/09 14:21:10 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "serveur.h"

void	usage(char *str)
{
	ft_putstr_fd("Usage: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(" <addr> <port>\n", 2);
	exit(-1);
}

int		check_args_client(int port)
{
	if (port > 49151 || port < 1024)
	{
		ft_putstr_fd("Invalid port\n", 2);
		return (-1);
	}
	return (0);
}
