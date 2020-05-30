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
#include <openkl/instruction.hpp>
#include <openkl/context.hpp>
#include "openkl/shims/kpu/kpu.hpp"


using namespace std;
using namespace stillwater::slm;

int main(int argc, char* argv[])
try {
	// set up the logger
	using namespace stillwater::diagnostics;
	Logger logger("shim-kpu-testbench");
	logger.addLogTarget(new ConsoleLogTarget()); // TODO: remote call to new
	logger.addLogTarget(new FileLogTarget());
	DIAG_INFO("kpu shim testbench starting");

	// create a KPU shim
	using kpushim = openkl::shim::KnowledgeProcessingUnit;
	constexpr size_t PROCS = 64;
	constexpr size_t MEMSIZE = SIZE_128M; // size of the channel DRAM
	constexpr size_t PAGESIZEINBYTES = 4096;
	constexpr size_t NRCHAN = 4;
	auto kpu = std::make_unique<kpushim>(PROCS, MEMSIZE, PAGESIZEINBYTES, NRCHAN);  // <-- a little error-prone to define this
	if (kpu == 0) {
		return EXIT_FAILURE;
	}

	// create a functional simulator of a KPU
	kpu->create();
	using Real = float;
	openkl::object_id a = kpu->claim(16 * sizeof(Real));
	openkl::object_id b = kpu->claim(16 * sizeof(Real));
	openkl::object_id c = kpu->claim(16 * sizeof(Real));
	// TODO: how to put data into these blocks
	// ...
	openkl::klInstruction cmd;
	cmd.add(c, a, b);
	kpu->execute(cmd);   // TODO: how to get notified that cmd is done
	// TODO: report the results
	kpu->release(a);
	kpu->release(b);
	kpu->release(c);
	kpu->report(std::cout);

	return EXIT_SUCCESS;
}
catch (std::runtime_error& e) {
	cerr << e.what() << endl;
}
catch (...) {
	cerr << "Caught unexpected error" << endl;
}



