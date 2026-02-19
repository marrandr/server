/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerTools.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marrandr <marrandr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 17:11:47 by marrandr          #+#    #+#             */
/*   Updated: 2026/02/19 17:14:04 by marrandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void	Server::clear()
{
	std::cout << "----------Close server--------------\n";
	_closeAllSocket();
	_allClients.clear();
	_allPollFd.clear();
}

void	Server::_removeClient(int fdClient)
{
	int	i = -1;
	for (i = 0; i < (int)_allPollFd.size(); i++)
		if (_allPollFd[i].fd == fdClient)
			break;
	if (i >= 0)
		_allPollFd.erase(_allPollFd.begin() + i);
	i = -1;
	for (i = 0; i < (int)_allClients.size(); i++)
		if (_allClients[i].getFd() == fdClient)
			break;
	if (i >= 0)
		_allClients.erase(_allClients.begin() + i);
	std::cout << "[INFO] : A client deleted \n";
	close(fdClient);
}

void	Server::_closeAllSocket()
{
	for (unsigned int i = 0; i < _allPollFd.size(); i++)
		if (_allPollFd[i].fd > 0)
			close (_allPollFd[i].fd);
}

Client	*Server::findClient(int fd) const
{
	for (unsigned int i = 0; i < _allClients.size(); i++)
	{
		if (_allClients[i].getFd() == fd)
			return ((Client *)&_allClients[i]);
	}
	return (NULL);
}
