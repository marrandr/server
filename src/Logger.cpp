/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Logger.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marrandr <marrandr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 09:12:20 by marrandr          #+#    #+#             */
/*   Updated: 2026/02/27 09:34:41 by marrandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Logger.hpp"

void Logger::log(Level lvl, const std::string& msg)
{
	switch (lvl)
	{
	case DEBUG:
		debug(msg);
		break;
	case INFO:
		info(msg);
		break;
	case WARNING:
		warning(msg);
		break;
	case ERROR:
		error(msg);
		break;
	default:
		break;
	}
}
void Logger::debug(const std::string& msg)
{
	std::cout << CYAN <<":[DEBUG] : " << msg << RESET <<std::endl;
}
void Logger::info(const std::string& msg)
{
	std::cout<< BLUE << ":[INFO] : " << msg << RESET <<std::endl;
}
void Logger::warning(const std::string& msg)
{
	std::cout << YELLOW << ":[WARNING] : " << msg << RESET <<std::endl;
}
void Logger::error(const std::string& msg)
{
	std::cerr << RED << ":[ERROR] : " << msg << RESET << std::endl;
}
