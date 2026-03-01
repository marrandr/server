/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marrandr <marrandr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 18:09:21 by marrandr          #+#    #+#             */
/*   Updated: 2026/03/01 09:50:32 by marrandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP
#include <unistd.h>
#include <iostream>
#include <string.h>
#include <vector>
#include <ctype.h>
#include <sys/types.h>
#include <netinet/ip.h>
#include <signal.h>
#include <poll.h>
#include <map>
#include <cstdlib>

#include "Client.hpp"
#include "ClientManager.hpp"
#include "Channel.hpp"
#include "Command.hpp"
#include "ircReplyCode.hpp"

#include "Config.hpp"
#include "ChannelManager.hpp"

extern sig_atomic_t gRun;

class Command;

class Server
{
	private:
		Config									_config;
		int					 					_serverSocket;

		//std::map<std::string, Channel*>			_allChannelByName;

		ClientManager							_cltManager;
		ChannelManager							_channelManager;

		std::vector<struct pollfd>				_allPollFd;
		std::string								_dateServer;
		void									_newConnection();
		void									_recevDataClient(int fdClient);
		void									_sendToClient(int fdClient);
		void									_closeAllSocket();

	public:
	Server(const Config& config);
		void	creatServerSocket();
		void	ConfigSocket();
		void	init();
		void	run();
		void	stop();
		void	clearData();

		//
		//Channel* getChannelByName(const std::string &channel);
		//void add_channel(Channel*ch);
		//bool Channel_exists(const std::string&c_name)const;
		//Channel* getChannel(const std::string&c_name);
		//

		void	removeFdInPoll(int fd);

		ChannelManager& getChannelManager();
		const ClientManager& getCltManager() const;
		void	setCltManager(Client* client, const std::string& oldNick, const std::string& newNick);

		const std::string& getDateServer() const;

		void errorInLoop(unsigned int index, int fdClient);

		const Config& getConfig() const;


};

void	serverUsage(const std::string &ServerName);
void	checkArgServer(const std::string &serverName, const std::string &port,  const std::string &pass);

#endif
