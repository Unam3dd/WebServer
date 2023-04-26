#include "signals.hpp"
#include "http_utils.hpp"
#include "http_colors.hpp"
#include "webserver.hpp"
#include <iostream>
#include <signal.h>

void	sig_handler(int sig)
{
	WebServer	*ptr = SG_WebServer(NULL);

	if (sig == SIGINT) {
		std::cout << INFO << "[sig_handler] Closing server wait a moment please !" << std::endl;
		ptr->SetRun(false);
	}
}

int	sig_setup(void)
{
	int	sig[MAX_SIG] = { SIGINT, SIGPIPE };

	for (int i = 0; i < MAX_SIG; i++)
		signal(sig[i], sig_handler);

	return (0);
}
