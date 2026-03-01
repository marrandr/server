/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChannelTool.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marrandr <marrandr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 17:28:19 by marrandr          #+#    #+#             */
/*   Updated: 2026/03/01 08:52:17 by marrandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Channel.hpp"
#include "../include/Client.hpp"

bool Channel::isInThisChannel(Client *client) const
{
	std::set<Client*>::iterator it = _clients.find(client);
	if (it != _clients.end())
		return (true);
	else
		return (false);
}

//void	Channel::send_to_member(Client *client, const std::string &msg)
//{
//	std::set<Client*>::iterator it;
//	for (it = _clients.begin(); it != _clients.end(); ++it)
//	{
//		if (client != *it)
//		{
//			(*it)->catsendBuffer(msg);
//		}
//	}
//}

