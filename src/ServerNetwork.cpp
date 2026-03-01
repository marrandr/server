/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerNetwork.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marrandr <marrandr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 17:10:10 by marrandr          #+#    #+#             */
/*   Updated: 2026/03/01 09:55:55 by marrandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Server.hpp"
#include "../include/Command.hpp"

void	Server::_newConnection()
{
	int					clientSocket = 1;
	struct sockaddr_in	sinClient;
	unsigned int		sizeLen = sizeof(sinClient);

	if (_cltManager.getNbClient() > MAX_CLIENT)
	{
		Logger::log(WARNING, "max client on server now");
		return ;
	}
	clientSocket = accept(_serverSocket, (struct sockaddr *)&sinClient, &sizeLen);
	if (clientSocket == -1)
	{
		_closeAllSocket();
		Logger::log(ERROR, "Accept have a problem");
		return ;
	}
	Logger::log(INFO, "New client try to connect");
	Client *client = new Client(clientSocket);
	struct pollfd pFdClient;
	_cltManager.addClient(client);
	pFdClient.fd = clientSocket;
	pFdClient.events = POLLIN | POLLOUT;
	pFdClient.revents = 0;
	_allPollFd.push_back(pFdClient);
}

void	Server::_recevDataClient(int fdClient)
{
	char	buffer[BUFFER_SIZE] = {0};
	Client	*client = NULL;
	Command	cmd(*this);

	ssize_t retRecv = recv(fdClient, buffer, BUFFER_SIZE - 1, 0);
	if (retRecv <= 0)
	{
		_cltManager.removeClient(fdClient);
		removeFdInPoll(fdClient);
		Logger::log(INFO, "A client is deconnect");
		return;
	}
	buffer[retRecv] = 0;

	write (1, "\n:[DEBUG] : all message --> ", 28);
	int i = 0;
	while (buffer[i])
	{
		if (buffer[i] == '\r')
			write(1, "\\r", 2);
		else if (buffer[i] == '\n')
			write(1, "\\n", 2);
		else
			write(1, &buffer[i], 1);
		i++;
	}
	write (1, "\n", 1);
	client = _cltManager.findByFd(fdClient);
	if (!client)
		return ;
	client->catrecvBuffer(buffer);
	cmd.handleDataReceve(client);
}

void	Server::_sendToClient(int fdClient)
{
	Client *client = _cltManager.findByFd(fdClient);
	if (!client || (client && client->get_sendBuffer().empty()))
		return ;
	ssize_t	lenBuff = client->get_sendBuffer().length();
	ssize_t	retSend = send(fdClient, client->get_sendBuffer().c_str(), lenBuff, MSG_NOSIGNAL);
	if (retSend == -1)
	{
		Logger::log(WARNING, "try send msg for client deconnect");
		_cltManager.removeClient(fdClient);
	}
	else if (retSend < lenBuff)
		client->set_sendBuffer(client->get_sendBuffer().substr(lenBuff - retSend));
	else
		client->set_sendBuffer("");
}
