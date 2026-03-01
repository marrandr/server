/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marrandr <marrandr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 09:49:33 by arasoloa          #+#    #+#             */
/*   Updated: 2026/03/01 09:02:20 by marrandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parse.hpp"

namespace parser {

	std::vector<std::string> split_buff(const std::string &buff)
	{
		std::vector<std::string> line;
		std::string::size_type start = 0;
		std::string::size_type end;
		std::string sep = "\r\n";

		while((end = buff.find(sep, start)) != std::string::npos)
		{
			std::string sub = buff.substr(start, end - start);
			if(!sub.empty())
				line.push_back(sub);
			start = end + sep.size();
		}
		if(start < buff.size())
		{
			std::string rest = buff.substr(start);
			if(!rest.empty())
				line.push_back(rest);
		}
		return (line);
	}

	size_t sapcePlace(const std::string &str)
	{
		size_t i = 0;
		while(i < str.size() && str[i] == ' ')
			i++;
		return(i);
	}


	std::string trimLeft(const std::string &str, int place)
	{
		size_t i = 0;

		if (place == 0)
		{
			while(i < str.size() && (str[i] == ' ' || str[i] == '\t'))
				i++;
		}
		else if (place == 1)
		{
			while(i < str.size() && str[i] == ' ')
				i++;
		}
		return (str.substr(i));
	}


	void fill_parse(t_parse &parse, std::string &line)
	{
		std::string trailing;
		size_t traiPos = line.find(':');
		if (traiPos != std::string::npos)
		{
			trailing = line.substr(traiPos + 1);
			line = line.substr(0 ,traiPos);
		}

		std::stringstream ss(line);
		std::string cmd;
		if(ss >> cmd)
		{
			std::transform(cmd.begin(), cmd.end(), cmd.begin(), ::toupper);
			parse.command = cmd;
		}

		std::string params;
		while(ss >> params)
			parse.params.push_back(params);
		if(!trailing.empty())
			parse.params.push_back(trailing);
	}

	void fill_error(t_parse &parse, std::string code, std::string msg)
	{
		parse.error_code = code;
		parse.error_msg = msg;
	}


	void fill_lst_param(t_parse &parse)
	{
		if(!parse.params.empty())
		{
			std::stringstream ss(parse.params[0]);
			std::string token;
			while (std::getline(ss, token, ','))
			{
				std::transform(token.begin(), token.end(), token.begin(), ::tolower);
				parse.lst_param.push_back(token);
			}
		}
	}

	t_parse parse_command(const std::string &cmd)
	{
		t_parse parse;

		std::string line = trimLeft(cmd, 0);

		size_t it_space = sapcePlace(line);
		if(line[0] == ':')
		{
			line = trimLeft(line.substr(it_space), 1);
		}
		fill_parse(parse, line);
		fill_lst_param(parse);
		return (parse);
	}

	std::vector<t_parse> finalizeParse(const std::string &buffer)
	{
		std::vector<t_parse> ret;

		std::vector<std::string> test = split_buff(buffer);
		std::vector<std::string>::iterator fin = test.end();
		for(std::vector<std::string>::iterator it = test.begin(); it != fin; it++)
		{
			t_parse cmd = parse_command(*it);
			checkErrors(cmd);
			ret.push_back(cmd);
		}
		return(ret);
	}
}

