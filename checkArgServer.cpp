/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkArgServer.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marrandr <marrandr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 18:09:50 by marrandr          #+#    #+#             */
/*   Updated: 2026/02/18 17:27:31 by marrandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

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
		std::cerr << "Non-existent port" <<std::endl;
		serverUsage(serverName);
		exit(1);
	}
	if (pass.empty())
	{
		std::cerr << "Invalid password, try again\n";
		serverUsage(serverName);
		exit(1);
	}
}
