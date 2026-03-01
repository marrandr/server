/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marrandr <marrandr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 11:21:41 by marrandr          #+#    #+#             */
/*   Updated: 2026/02/27 11:33:55 by marrandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Utils.hpp"

bool Utils::isValidNick(const std::string &nick) {
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

bool Utils::isValidChannel(const std::string &chan){
    if (chan.empty() || chan.size() > 200) return false;
    if (chan[0] != '#' && chan[0] != '&') return false;
    for (size_t i = 1; i < chan.size(); ++i) {
        char c = chan[i];
        if (!(isalnum(c) || c == '-' || c == '_' || c == '#' || c == '&' || c == '[' || c == ']' || c == '\\' ||
              c == '^' || c == '{' || c == '}' || c == '|')) return false;
    }
    return true;
}


std::string Utils::getDateTimeNow()
{
	time_t now = time(NULL);
	std::string	date = ctime(&now);

	if (!date.empty() && date[date.length() - 1] == '\n')
		date.erase(date.length()- 1);
	return (date);
}
