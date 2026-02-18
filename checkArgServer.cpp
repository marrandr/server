/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkArgServer.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marrandr <marrandr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 18:09:50 by marrandr          #+#    #+#             */
/*   Updated: 2026/02/17 18:09:52 by marrandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void	checkArgServer(const std::string &serverName, const std::string &port)
{
	int isDigit = 1;

	for (int i = 0; i < port.length(); i++)
		if (!isdigit((int)port[i]))
		{
			isDigit = 0;
			break ;
		}
	if (port.length() > 5 || !isDigit)
	{
		std::cerr << "Non-existent port" <<std::endl;
		serverUsage(serverName);
		exit(1);
	}
}
