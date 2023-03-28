#include "signals.hpp"
#include <signal.h>
#include "http_utils.hpp"
#include "utils.hpp"
#include "webserver.hpp"
#include <iostream>

void	sig_handler(int sig)
{
	WebServer	*ptr = SG_WebServer(NULL);

	if (sig == SIGINT) {
		std::cout << "[+] Closing server wait a moment please ! take your coffee !" << std::endl;
		ptr->SetRun(false);
	}
}

int	sig_setup(void)
{
	int	sig[MAX_SIG] = { SIGINT };

	for (int i = 0; i < MAX_SIG; i++)
		signal(sig[i], sig_handler);

	return (0);
}
