/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientManager.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marrandr <marrandr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 17:33:58 by marrandr          #+#    #+#             */
/*   Updated: 2026/03/01 09:37:42 by marrandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClientManager.hpp"

ClientManager::ClientManager()
{}

ClientManager::~ClientManager()
{}

size_t	ClientManager::getNbClient() const
{
	return (_allClientsByFd.size());
}


const std::map<std::string, Client*>&	ClientManager::getClientByNick() const
{
	return (_allClientsByNick);
}

void	ClientManager::addClient(Client* client)
{
	_allClientsByFd.insert(std::make_pair(client->getFd(), client));
	_allClientsByNick.insert(std::make_pair(client->getNickName(), client));
}

void ClientManager::removeClient(int fd)
{
	std::map<int, Client*>::iterator it = _allClientsByFd.find(fd);
	if (it != _allClientsByFd.end())
	{
		std::string nick = it->second->getNickName();
		delete	it->second;
		_allClientsByFd.erase(fd);
		_allClientsByNick.erase(nick);
		//
		close(fd);
	}
}

Client* ClientManager::findByFd(int fd) const
{
	std::map<int, Client*>::const_iterator it = _allClientsByFd.find(fd);
	if (it != _allClientsByFd.end())
		return (it->second);
	else
		return (NULL);
}

Client*	ClientManager::findByNick(const std::string& nick) const
{
	std::map<std::string, Client*>::const_iterator it = _allClientsByNick.find(nick);
	if (it != _allClientsByNick.end())
		return (it->second);
	else
		return (NULL);
}

bool	ClientManager::insNickUse(const std::string& nick) const
{
	if (findByNick(nick))
		return (true);
	else
		return (false);
}

void	ClientManager::updateNickName(Client* client, const std::string& oldNick, const std::string& newNick)
{
	std::map<std::string, Client*>::const_iterator itNick = _allClientsByNick.find(oldNick);
	if (itNick != _allClientsByNick.end())
	{
		_allClientsByNick.erase(oldNick);
	}
	client->setNickName(newNick);
	_allClientsByNick.insert(std::make_pair(newNick, client));
}

std::set<Client *> ClientManager::getClientsCommonChannels(Client* client) const
{
	std::set<Client *> res;
	for (std::set<Channel *>::const_iterator itChan = client->getChannels().begin(); itChan != client->getChannels().end() ; ++itChan)
	{
		std::set<Client *> CliOnChan = (*itChan)->getClients();
		for (std::set<Client *>::const_iterator itCli = CliOnChan.begin() ; itCli != CliOnChan.end() ; ++itCli)
		{
			if (*itCli != client)
				res.insert(*itCli);
		}
	}
	return (res);
}

void	ClientManager::clear()
{
	std::map<int, Client*>::const_iterator it;
	for (it = _allClientsByFd.begin(); it != _allClientsByFd.end(); ++it)
		if (it->second)
			delete it->second;
	_allClientsByFd.clear();
	_allClientsByNick.clear();
}

