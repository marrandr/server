/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseValide.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marrandr <marrandr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 15:38:49 by marrandr          #+#    #+#             */
/*   Updated: 2026/02/28 15:43:02 by marrandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parse.hpp"

namespace parser {

	bool isValidNick(const std::string &nick) {
		if (nick.empty() || nick.size() > 9) return false;
		char n = nick[0];
		if (!(isalpha(n) || n == '-' || n == '[' || n == ']' || n == '\\' ||
				n == '^' || n == '{' || n == '}' || n == '|' || n == '_'))
				return false;
		for (size_t i = 1; i < nick.size(); ++i) {
			char c = nick[i];
			if (!(isalnum(c) || c == '-' || c == '[' || c == ']' || c == '\\' ||
				c == '^' || c == '{' || c == '}' || c == '|' || c == '_'))
				return false;
		}
		return true;
	}

	bool hasInvalidSpace(t_parse parse)
	{
		for(size_t i = 0; i < parse.command.size(); i++)
		{
			char c = parse.command[i];
			if (c == '\t' || c == '\r' || c == '\n')
				return true;
		}
		return (false);
	}

	bool isValidUser(const std::string &nick) {
		if (nick.empty() || nick.size() > 512) return false;
		for (size_t i = 0; i < nick.size(); ++i) {
			char c = nick[i];
			if (!(isalnum(c) || c == '-' || c == '[' || c == ']' || c == '\\' ||
				c == '^' || c == '{' || c == '}' || c == '|' || c == '_'))
				return false;
		}
		return true;
	}

	bool validCmd(const std::string &cmd)
	{
		std::string tab[11] = {"PASS", "NICK" , "USER", "JOIN", "PRIVMSG", "PING", "PONG" , "QUIT", "EXIT", "CAP", "MODE"};
		int index = -1;
		for(int i = 0 ; i < 11; i++)
		{
			if(tab[i] == cmd)
				index = i;
		}
		if(index == -1)
			return (false);
		return (true);
	}

	void checkErrors(t_parse &parse)
	{
		if (parse.command == "NICK" && parse.params.size() < 1) {
			fill_error(parse, ERR_NEEDMOREPARAMS, ERR_NEEDMOREPARAMS_MSG);
			return;
		}
		if (parse.command == "NICK" && !isValidNick(parse.params[0])) {
			fill_error(parse, ERR_ERRONEUSNICKNAME, ERR_ERRONEUSNICKNAME_MSG);
			return;
		}
		if (parse.command == "USER" && parse.params.size() < 4) {
			fill_error(parse, ERR_NEEDMOREPARAMS, ERR_NEEDMOREPARAMS_MSG);
			return;
		}
		if (parse.command == "USER" && !isValidUser(parse.params[0])) {
			fill_error(parse, ERR_INVALIDUSERNAME, ERR_INVALIDUSERNAME_MSG);
			return;
		}
		if (parse.command == "JOIN" && parse.params.size() < 1) {
			fill_error(parse, ERR_NEEDMOREPARAMS, ERR_NEEDMOREPARAMS_MSG);
			return;
		}

		if (parse.command == "PRIVMSG" && parse.params.empty())
		{
			fill_error(parse, ERR_NORECIPIENT ,ERR_NORECIPIENT_MSG);
			return;
		}
		if (parse.command == "PRIVMSG" && parse.params.size() == 1)
		{
			fill_error(parse, ERR_NOTEXTTOSEND ,ERR_NOTEXTTOSEND_MSG);
			return;
		}
		if (parse.command == "CAP" && parse.params.size() < 1)
		{
			fill_error(parse, ERR_NEEDMOREPARAMS, ERR_NEEDMOREPARAMS_MSG);
			return;
		}
		if (parse.command == "MODE" && parse.params.size() < 1)
		{
			fill_error(parse, ERR_NEEDMOREPARAMS, ERR_NEEDMOREPARAMS_MSG);
			return;
		}
		if (parse.command == "PING" && (parse.params.empty() || parse.params[0].empty()))
		{
			fill_error(parse, ERR_NOORIGIN, ERR_NOORIGIN_MSG);
			return;
		}
		if (!validCmd(parse.command) || hasInvalidSpace(parse))
		{
			fill_error(parse, ERR_UNKNOWNCOMMAND ,ERR_UNKNOWNCOMMAND_MSG);
			return;
		}
	}
}
