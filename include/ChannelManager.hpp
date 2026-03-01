/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChannelManager.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marrandr <marrandr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 05:59:42 by marrandr          #+#    #+#             */
/*   Updated: 2026/03/01 09:05:26 by marrandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNELMANAGER_HPP
#define CHANNELMANAGER_HPP

#include <map>
#include <vector>
#include <string>
#include "Channel.hpp"
#include "Client.hpp"

class ChannelManager
{
	private:
		std::map<std::string, Channel*> _allChannelByName;

	public:
		ChannelManager();
		~ChannelManager();
		void	clear();

		void createChannel(const std::string& name, Client* creator);
		Channel* findChannel(const std::string& name) const;
		bool channelExists(const std::string& name) const;
		void removeChannel(const std::string& name);
		void removeEmptyChannels();

		std::vector<Channel*> getChannelsClient(Client* client) const;
		void broadcastToChannel(Channel* channel, const std::string& msg, Client* exclu);

};

#endif
