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

std::string attributes(openkl::klExecutionEnvironment& target) {
	std::stringstream ss;
	ss << "+-----\n"
		<< " target             : " << target.id << '\n'
		<< " compute class      : " << openkl::klComputeResourceTypeString[target.procType] << '\n'
		<< " cores              : " << target.cores << '\n'
		<< " threads            : " << target.threads << '\n'
		<< " core frequency     : " << target.freq << '\n'
		<< " memory class       : " << openkl::klMemoryResourceTypeString[target.memType] << '\n'
		<< " memory size        : " << target.size << " MBytes\n"
		<< " memory channels    : " << target.channels << '\n'
		<< " memory page size   : " << target.pageSize << " kBytes";
	return ss.str();
}

void ShowInventory(openkl::klComputeTargets& targets) {
	std::cout << "\nInventory of compute resource targets\n";
	for (int i = 0; i < targets.size(); ++i) {
		std::cout << attributes(targets[i]) << std::endl;
	}
	std::cout << std::endl;
}

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
	for (int i = 0; i < proxy->nrTargets(); ++i) {
		std::cout << attributes(proxy->getTarget(i)) << std::endl;
	}
	return EXIT_SUCCESS;
}
catch (std::runtime_error& e) {
	cerr << e.what() << endl;
}
catch (...) {
	cerr << "Caught unexpected error" << endl;
}


