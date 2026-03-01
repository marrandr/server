/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChannelManager.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marrandr <marrandr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 06:05:26 by marrandr          #+#    #+#             */
/*   Updated: 2026/03/01 09:05:36 by marrandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ChannelManager.hpp"

ChannelManager::ChannelManager()
{}

ChannelManager::~ChannelManager()
{}

void ChannelManager::clear()
{
	for (std::map<std::string, Channel*>::iterator it = _allChannelByName.begin(); it != _allChannelByName.end(); ++it)
	{
		if (it->second)
			delete it->second;
	}
	_allChannelByName.clear();
}

void ChannelManager::createChannel(const std::string& name, Client* creator)
{
	Channel	*chan = new Channel(name);
	chan->add_client(creator);
	chan->add_operator(creator);
	creator->joinChannel(chan);
	_allChannelByName.insert(std::make_pair(name, chan));

}

Channel* ChannelManager::findChannel(const std::string& name) const
{
	std::map<std::string, Channel*>::const_iterator it = _allChannelByName.find(name);
	if (it != _allChannelByName.end())
		return (it->second);
	else
		return (NULL);
}

bool ChannelManager::channelExists(const std::string& name) const
{
	std::map<std::string, Channel*>::const_iterator it = _allChannelByName.find(name);
	if (it != _allChannelByName.end())
		return (true);
	else
		return (false);
}

void ChannelManager::removeChannel(const std::string& name)
{
	std::map<std::string, Channel*>::iterator it = _allChannelByName.find(name);
	if (it != _allChannelByName.end())
	{
		delete it->second;
		_allChannelByName.erase(name);
	}
}

void ChannelManager::removeEmptyChannels()
{
	std::map<std::string, Channel*>::iterator	it;
	for (it = _allChannelByName.begin(); it != _allChannelByName.end(); ++it)
	{
		if (it->second->getNbUserChannel() == 0)
		{
			std::string chanName = it->second->getName();
			delete it->second;
			_allChannelByName.erase(chanName);
		}
	}
}
std::vector<Channel*>  ChannelManager::getChannelsClient(Client* client) const
{
	std::vector<Channel*> res;

	if (!client)
	return (res);
	const std::set<Channel*> allCha = client->getChannels();
	std::set<Channel*>::const_iterator it;
	for (it = allCha.begin(); it != allCha.end(); ++it)
	{
		res.push_back(*it);
	}
	return (res);
}

void  ChannelManager::broadcastToChannel(Channel* channel, const std::string& msg, Client* exclu)
{
	std::set<Client*> allCli = channel->getClients();
	for (std::set<Client*>::iterator it = allCli.begin(); it != allCli.end(); ++it)
	{
		if (*it != exclu)
			(*it)->catsendBuffer(msg);
	}
}

