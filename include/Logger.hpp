/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Logger.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marrandr <marrandr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 09:06:12 by marrandr          #+#    #+#             */
/*   Updated: 2026/02/27 13:58:31 by marrandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOGGER_HPP
#define LOGGER_HPP
#include <string>
#include <iostream>

#define RED     "\033[31m"
#define YELLOW  "\033[33m"
#define BLUE	"\033[34m"
#define CYAN	"\033[36m"
#define RESET   "\033[0m"

enum Level {DEBUG, INFO, WARNING, ERROR};

class Logger
{
	public:
		static void log(Level lvl, const std::string& msg);
		static void debug(const std::string& msg);
		static void info(const std::string& msg);
		static void warning(const std::string& msg);
		static void error(const std::string& msg);
};

#endif
