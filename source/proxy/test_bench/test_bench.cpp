// test_bench.cpp : unit level test bench for the proxy library
//

// STL headers
#include <iostream>
#include <iomanip>
#include <map>
#include <tchar.h>
// STILLWATER headers
#include <stillwater/baseTypes.hpp>
#include <stillwater/exceptions.hpp>
#include <interfaces/MemoryTypeEnums.hpp>		// ETLO 2/23/07 This is an odd dependency on the namespace definition TODO fix this if you can
// diagnostic services
#define STILLWATER_DIAGNOSTICS
#include <stillwater/diagnostics.hpp>
#include <stillwater/automation.hpp>

// OpenKL proxy
#include <openkl/proxy/proxy.hpp>

using namespace std;

int main(int argc, char* argv[])
try {
	// set up the logger
	using namespace stillwater::diagnostics;
	Logger logger("test_proxy");
	logger.addLogTarget(new ConsoleLogTarget());
	logger.addLogTarget(new FileLogTarget());
	DIAG_INFO("proxy testbench starting");

	// get a hold of the proxy
	openkl::proxy* proxy = openkl::proxy::getInstance();
	cout << "Nr of targets found: " << proxy->nrTargets() << endl;

	return EXIT_SUCCESS;
}
catch (std::runtime_error& e) {
	cerr << e.what() << endl;
}
catch (...) {
	cerr << "Caught unexpected error" << endl;
}


