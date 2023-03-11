/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   request_config.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stales <stales@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 13:49:21 by stales            #+#    #+#             */
/*   Updated: 2023/03/11 14:31:36 by stales           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQUEST_CONFIG_HPP
#define REQUEST_CONFIG_HPP

#include <string>

class RequestConfig
{
	public:
		RequestConfig(void);
		~RequestConfig(void);

	/*
	 * Accessors
	 */
	
	inline const std::string&	GetPath(void) const { return (_impl->_path); }
	const std::string&	GetMethods(void) const { return (_impl->_methods); }
	const std::string&	GetRedirects(void) const { return (_impl->_redirects); }
	const std::string&	GetDocRoots(void) const { return (_impl->_docroot); }
	const std::string&	GetDirList(void) const { return (_impl->_dirlist); }
	const std::string&	GetIndex(void) const { return (_impl->_index); }
	const std::string&	GetCgi(void) const { return (_impl->_cgi); }
	const std::string&	GetUpload(void) const { return (_impl->_upload); }
	const std::string&	GetDefaultErrPages(void) const { return (_impl->_default_err_pages); }

	void		SetPath(const std::string& path);
	void		SetMethods(const std::string& methods);
	void		SetRedirects(const std::string& redirects);
	void		SetDocRoot(const std::string& docroot);
	void		SetDirList(const std::string& dirlist);
	void		SetIndex(const std::string& index);
	void		SetCgi(const std::string& cgi);
	void		SetUpload(const std::string& upload);
	void		SetDefaultErrPages(const std::string& dep);
	
	private:
		struct Pimpl
		{
			std::string	_path;
			std::string	_methods;
			std::string	_redirects;
			std::string	_docroot;
			std::string	_dirlist;
			std::string	_index;
			std::string	_cgi;
			std::string _upload;
			std::string _default_err_pages;
		};
		Pimpl* _impl;
};

#endif
