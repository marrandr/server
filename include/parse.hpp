/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marrandr <marrandr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 11:00:18 by arasoloa          #+#    #+#             */
/*   Updated: 2026/02/28 15:44:01 by marrandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_HPP
#define PARSE_HPP


#include <unistd.h>
#include <cstring>
#include <iostream>
#include <vector>
#include <algorithm>
#include <exception>
#include <sstream>
#include <sys/socket.h>
#include "ircReplyCode.hpp"

typedef struct s_parse
{
    std::string                 command;
    std::vector<std::string>    params;
    std::vector<std::string>   lst_param;
    std::string                 error_code;
    std::string                 error_msg;
}               t_parse;
namespace parser {
	std::vector<t_parse> finalizeParse(const std::string &buffer);
	void checkErrors(t_parse &parse);
	void fill_error(t_parse &parse, std::string code, std::string msg);
}

#endif
