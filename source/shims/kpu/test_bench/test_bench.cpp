// test_bench.cpp : unit level test bench for the memory resource management library
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
// STILLWATER SLM components
#include <stillwater/arch/baseTypes/slmBaseTypes_nsmacro.hpp>
#include <stillwater/arch/baseTypes/Request.hpp>
// Library headers and supporting types
#include "openkl/shims/kpu/kpu.hpp"


using namespace std;
using namespace stillwater::slm;

int main(int argc, char* argv[])
try {
	// set up the logger
	using namespace stillwater::diagnostics;
	Logger logger("shim-kpu-testbench");
	logger.addLogTarget(new ConsoleLogTarget());
	logger.addLogTarget(new FileLogTarget());
	DIAG_INFO("kpu shim testbench starting");

	// gain access the default KPU shim
	openkl::shim::KnowledgeProcessingUnit* kpu = openkl::shim::KnowledgeProcessingUnit::getInstance();
	if (kpu == 0) {
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}
catch (std::runtime_error& e) {
	cerr << e.what() << endl;
}
catch (...) {
	cerr << "Caught unexpected error" << endl;
}



