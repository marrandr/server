/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerTools.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marrandr <marrandr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 17:11:47 by marrandr          #+#    #+#             */
/*   Updated: 2026/03/01 09:54:07 by marrandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Server.hpp"

void	Server::removeFdInPoll(int fd)
{
	for (size_t i = 0; i < _allPollFd.size(); i++)
	{
		if (_allPollFd[i].fd == fd)
		{
			_allPollFd.erase(_allPollFd.begin() + i);
			return;
		}
	}
}


void	Server::clearData()
{
	std::cout << "----------Close server--------------\n";
	_closeAllSocket();
	_cltManager.clear();
	_channelManager.clear();
	//std::map<std::string, Channel*>::iterator itChan;
	//for (itChan = .begin(); itChan != _allChannelByName.end(); ++itChan)
	//{
	//	if (itChan->second)
	//		delete itChan->second;
	//}
	_allPollFd.clear();
	//_allChannelByName.clear();
}

void	Server::_closeAllSocket()
{
	for (unsigned int i = 0; i < _allPollFd.size(); i++)
		if (_allPollFd[i].fd > 0)
			close (_allPollFd[i].fd);
}

const Config& Server::getConfig() const
{
	return (_config);
}
