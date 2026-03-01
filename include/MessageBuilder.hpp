/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MessageBuilder.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marrandr <marrandr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 13:54:42 by marrandr          #+#    #+#             */
/*   Updated: 2026/02/27 15:39:16 by marrandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MESSAGEBUILDER_HPP
#define MESSAGEBUILDER_HPP

#include <string>
#include "ircReplyCode.hpp"
#include "Utils.hpp"

class MessageBuilder
{
	public:
	static std::string error(
		const std::string& svrName,
		const std::string& code,
		const std::string& nick,
		const std::string& target,
		const std::string& msg
	);
	static std::string reply(
		const std::string& svrName,
		const std::string& code,
		const std::string& nick,
		const std::string& msg
	);
	static std::string command(
    const std::string& prefix,
    const std::string& cmd,
    const std::string& params,
    const std::string& trailing
	);
	static std::string welcome(
    const std::string& svrName,
    const std::string& nick,
    const std::string& user,
    const std::string& host,
	const std::string& serverDate
	);
};

#endif
