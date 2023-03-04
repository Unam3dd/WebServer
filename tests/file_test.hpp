/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_test.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sam0verfl0w <stales@student.42angouleme.f  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 19:31:45 by sam0verfl0w       #+#    #+#             */
/*   Updated: 2023/03/04 20:36:57 by sam0verfl0w      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILE_TEST_HPP
#define FILE_TEST_HPP

#include "greatest/greatest.h"
#include "file.hpp"
#include <cstdlib>
#include <fcntl.h>
#include <unistd.h>

TEST	file_test1(void)
{
	char	buf[0x100];

	getcwd(buf, sizeof(buf));
	if (chdir(buf) < 0)
		FAIL();
	system("echo -n 'hello world' > test.txt");
	File	f("test.txt", O_RDONLY, S_IRUSR);
	f.read();
	ASSERT_STR_EQ("hello world", f.getData());
	ASSERT_EQ(strlen("hello world"), f.length());
	f.~File();
	system("rm -rf test.txt");
	ASSERT_EQ(NULL, f.getData());
	ASSERT_EQ(f.getFd(), -1);
	PASS();
}

TEST	file_test2(void)
{
	char	buf[0x100];

	getcwd(buf, sizeof(buf));
	if (chdir(buf) < 0)
		FAIL();
	system("mkdir mdr");
	File	f;
	ASSERT_EQ(f.open("mdr", O_RDONLY, S_IRUSR), false);
	system("rm -rf mdr");
	PASS();
}

TEST	file_test3(void)
{
	char	buf[0x100];

	getcwd(buf, sizeof(buf));
	if (chdir(buf) < 0)
		FAIL();
	system("touch lol && chmod 000 lol");
	File	f;
	ASSERT_EQ(f.open("lol", O_RDONLY, S_IRUSR), false);
	system("rm -rf lol");
	PASS();
}

TEST	file_test4(void)
{
	File	f;
	ASSERT_EQ(f.open("test123", O_RDONLY, S_IRUSR), false);
	PASS();
}

#endif
