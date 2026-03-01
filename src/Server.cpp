/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marrandr <marrandr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 14:32:39 by marrandr          #+#    #+#             */
/*   Updated: 2026/03/01 09:37:57 by marrandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Server.hpp"

Server::Server(const Config& config) : _config(config), _serverSocket(-1)
{
	_dateServer = Utils::getDateTimeNow();
}

const std::string& Server::getDateServer() const
{
	return (_dateServer);
}

const ClientManager& Server::getCltManager() const
{
	return (_cltManager);
}

ChannelManager& Server::getChannelManager()
{
	return (_channelManager);
}

void	Server::setCltManager(Client* client, const std::string& oldNick, const std::string& newNick)
{
	_cltManager.updateNickName(client, oldNick, newNick);
}

void	Server::creatServerSocket()
{
	//create socket
	_serverSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (_serverSocket == -1)
	{
		Logger::log(ERROR, "can 't creat socket");
		exit(1);
	}
}

void	Server::ConfigSocket()
{
	struct sockaddr_in sin;
	int	opt = 1;
	//Prepare Bind
	if (setsockopt(_serverSocket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1)
	{
		Logger::log(ERROR, "can't prepare bind by Setockopt");
		close(_serverSocket);
		exit(1);
	}
	Logger::log(INFO, "Socket creat ");
	//init data sockaddr_in for bind
	sin.sin_port = htons(this->_config.getPort());
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind(_serverSocket, (struct sockaddr *)&sin, sizeof(sin)) == -1)
	{
		Logger::log(ERROR, "can't init bind");
		close(_serverSocket);
		exit(1);
	}
	Logger::log(INFO, "Bind init");
	//listen
	if (listen(_serverSocket, MAX_CLIENT) == -1)
	{
		Logger::log(ERROR, "can't init listen");
		close(_serverSocket);
		exit(1);
	}
	Logger::log(INFO, "Listen OK");
}

void	Server::init()
{
	std::cout<<"/* ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━ */\n";
	std::cout<<"/*                                FT_IRC                                 */\n";
	std::cout<<"/* ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━ */\n";
	std::cout << "----------Init server---------------\n";
	creatServerSocket();
	ConfigSocket();
	struct pollfd pFdServer;
	pFdServer.fd = _serverSocket;
	pFdServer.events = POLLIN | POLLOUT;
	_allPollFd.push_back(pFdServer);
	std::cout << "------------------------------------\n";
}

void	Server::run()
{
	std::cout << "-----------Run server----------------\n";
	int		retPoll = -1;

	while (gRun)
	{
		retPoll = poll(&_allPollFd[0], _allPollFd.size(), -1);
		if (retPoll < 0)
		{
			Logger::log(ERROR, "Poll faild");
			break;
		}
		for (unsigned int i = 0; i < _allPollFd.size(); i++)
		{
			if (_allPollFd[i].revents == 0)
				continue ;
			if (_allPollFd[i].revents & (POLLERR | POLLHUP | POLLNVAL))
				errorInLoop(i, _allPollFd[i].fd);
			else if (_allPollFd[i].revents & POLLIN)
			{
				if (i == 0)
					_newConnection();
				else
				{
					_recevDataClient(_allPollFd[i].fd);
					continue;
				}
			}
			else if (_allPollFd[i].revents & POLLOUT)
				_sendToClient(_allPollFd[i].fd);
		}
	}
	std::cout << "--------------------------------------\n";
}

void	Server::stop()
{
	clearData();
}
