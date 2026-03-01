/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MessageBuilder.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marrandr <marrandr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 14:11:46 by marrandr          #+#    #+#             */
/*   Updated: 2026/03/01 10:01:19 by marrandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/MessageBuilder.hpp"

std::string MessageBuilder::error(const std::string& svrName, const std::string& code, const std::string& nick, const std::string& target, const std::string& msg)
{
	std::string res = ":" + svrName + " " + code + " ";
	if (nick.empty())
		res += "*";
	else
		res += nick;
	if (!target.empty())
		res += " " + target;
	res += " :" + msg + END;
	return (res);
}

std::string MessageBuilder::reply(const std::string& svrName, const std::string& code, const std::string& nick, const std::string& msg)
{
	std::string res = ":" + svrName + " " + code + " " + nick + " :" + msg + END;
	return (res);
}

std::string MessageBuilder::command(const std::string& prefix,const std::string& cmd,const std::string& params,const std::string& trailing)
{
	std::string res = ":" + prefix + " " + cmd + " " + params;
	if (!trailing.empty())
		res += ": " + trailing;
	res += END;
	return (res);
}

std::string MessageBuilder::welcome(const std::string& svrName,const std::string& nick,const std::string& user,const std::string& host, const std::string& serverDate)
{
	std::string msgWelcom = ":" + svrName + " " + RPL_WELCOME + " " + nick + " :" + RPL_WELCOME_MSG + " " + user + "@" + host + END;
	msgWelcom += ":" + svrName + " " + RPL_YOURHOST + " " + nick + " :" + RPL_YOURHOST_MSG1 + " " + svrName + RPL_YOURHOST_MSG2 + SERVER_VERSION + END;
	msgWelcom += ":" + svrName + " " + RPL_CREATED + " " + nick + " :" + RPL_CREATED_MSG + " " + serverDate + END;
	msgWelcom += ":" + svrName + " " + RPL_MYINFO + " " + nick + " " + svrName + " version " + SERVER_VERSION + " o iklot" + END;
	return (msgWelcom);
}
