/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerError.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marrandr <marrandr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 11:52:44 by marrandr          #+#    #+#             */
/*   Updated: 2026/03/01 09:36:49 by marrandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Server.hpp"

void Server::errorInLoop(unsigned int index, int fdClient)
{
	(void)fdClient;
	if (index == 0)
	{
		Logger::log(ERROR, "[Error] : Server have bug");
		exit(1);
	}
	else
	{
		Logger::log(ERROR, "[Error] : Client have bug");
		//removeClient(fdClient);
	}
}
