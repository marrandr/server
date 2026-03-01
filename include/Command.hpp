/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marrandr <marrandr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 06:16:41 by marrandr          #+#    #+#             */
/*   Updated: 2026/02/28 19:25:19 by marrandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_HPP
#define COMMAND_HPP
#include "Server.hpp"
#include "parse.hpp"
#include "Logger.hpp"
#include "Utils.hpp"
#include "MessageBuilder.hpp"
#include "ClientManager.hpp"

class Server;

class Command
{
	private:
		Server &_server;

	public:
		Command(Server &srv);

		void	handleCap(Client *client, const t_parse &parse);
		void	handlePass(Client *client, const t_parse &parse);
		void	handleUser(Client *client, const t_parse &parse);
		void	handleNick(Client *client, const t_parse &parse);
		void	handlePrivmsg(Client *client, const t_parse &parse);

		void	sendToChannel(Client *client, const t_parse &parse, size_t indexLstParam, const std::string &msg);

		void	handleJoin(Client *client, const t_parse &parse);
		//void	handlePing(Client *client, const t_parse &parse);
		//void	handlePong(Client *client, const t_parse &parse);
		//void	handleQuit(Client *client, const t_parse &parse);
		//void	handleExit(Client *client, const t_parse &parse);

		void	handleDataReceve(Client *client);
		void	execute(Client *client, const t_parse &parse);
	};

#endif
