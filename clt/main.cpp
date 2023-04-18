#include "http_client.hpp"
#include <iostream>

int main(int ac, char **av)
{
	if (ac < 2) {
		std::cerr << "usage " << av[0] << " <url> " << std::endl;
		return (1);
	}

	HttpClient	client;

	client.get(av[1]);

	return (0);
}
