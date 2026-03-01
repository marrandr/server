/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkArgServer.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marrandr <marrandr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 18:09:50 by marrandr          #+#    #+#             */
/*   Updated: 2026/02/27 10:04:11 by marrandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Server.hpp"

void	checkArgServer(const std::string &serverName, const std::string &port,  const std::string &pass)
{
	int isDigit = 1;

	for (unsigned int i = 0; i < port.length(); i++)
		if (!isdigit((int)port[i]))
		{
			isDigit = 0;
			break ;
		}
	if (port.length() > 5 || !isDigit)
	{
		Logger::log(ERROR, ":Non-existent port");
		serverUsage(serverName);
		exit(1);
	}
	if (pass.empty())
	{
		Logger::log(ERROR,  ":Invalid password, try again");
		serverUsage(serverName);
		exit(1);
	}
}
