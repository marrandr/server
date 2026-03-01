/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marrandr <marrandr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 11:19:38 by marrandr          #+#    #+#             */
/*   Updated: 2026/02/27 13:57:26 by marrandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
#define UTILS_HPP

#include <ctime>
#include <string>

class Utils
{
	public:
		static bool isValidNick(const std::string &cmd);
		static bool isValidChannel(const std::string &chan);
		static std::string getDateTimeNow();

};

#endif
