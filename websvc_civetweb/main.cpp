#include <iostream>
#include <chrono>
#include <thread>

#include "CivetServer.h"
#include "webserver.h"



#define NO_SSL


#ifdef NO_SSL
#define PORT "8089"
#define HOST_INFO "http://localhost:8089"
#else
#define PORT "8089r,8843s"
#define HOST_INFO "https://localhost:8843"
#endif

#define DOCUMENT_ROOT "."
#define EXPERIMENT_URI "/api/exp"
#define EXIT_URI "/api/exit"
#define METHOD_FILES_URI "/api/method-files"





int main()
{
	std::cout << "websvc\n";

	// Show info
	std::cout << "Experiment Control: " << HOST_INFO << EXPERIMENT_URI << std::endl;
	std::cout << "Method Files: " << HOST_INFO << METHOD_FILES_URI << std::endl;
	std::cout << "Exit Experiment Service: " << HOST_INFO << EXIT_URI << std::endl;

	mg_init_library(0);

	const char* options[] = {
		"document_root", DOCUMENT_ROOT, "listening_ports", PORT, 0 };

	std::vector<std::string> cpp_options;
	for (int i = 0; i < (sizeof(options) / sizeof(options[0]) - 1); i++) {
		cpp_options.push_back(options[i]);
	}

	CivetServer server(cpp_options); // <-- C++ style start

	ExperimentHandler h_experiment;
	server.addHandler(EXPERIMENT_URI, h_experiment);




	/* Wait until the server should be closed */
	while (true) {
		using namespace std::chrono_literals;
		std::this_thread::sleep_for(2000ms);
	}




	return 0;
}