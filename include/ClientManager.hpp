/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientManager.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marrandr <marrandr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 17:18:32 by marrandr          #+#    #+#             */
/*   Updated: 2026/03/01 09:29:08 by marrandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENTMANAGER_HPP
#define CLIENTMANAGER_HPP

#include "Client.hpp"
#include <map>
#include <unistd.h>

class ClientManager
{
	private:
		std::map<std::string, Client*>			_allClientsByNick;
		std::map<int, Client*>					_allClientsByFd;

	public:
		ClientManager();
		~ClientManager();

		const std::map<std::string, Client*>&	getClientByNick() const;

		size_t	getNbClient() const;
		void	addClient(Client* Client);
		void	removeClient(int fd);
		Client*	findByFd(int fd) const;
		Client* findByNick(const std::string& nick) const;

		bool	insNickUse(const std::string& nick) const;
		void	updateNickName(Client* client, const std::string& oldNick, const std::string& newNick);

		std::set<Client *> getClientsCommonChannels(Client* client) const;
		void	clear();

};

#endif
