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
#include "../memory_nsmacro.hpp"	// centralized namespace definition
#include "../Page.hpp"
#include "../Memory.hpp"
#include "../MemoryDescriptor.hpp"
#include "../MemoryObject.hpp"
#include "../MobMemory.hpp"


using namespace std;
using namespace stillwater::slm;

int main(int argc, char* argv[])
{
	// set up the logger
	using namespace stillwater::diagnostics;
	Logger logger("memory-testbench");
	logger.addLogTarget(new ConsoleLogTarget());
	logger.addLogTarget(new FileLogTarget());
	DIAG_INFO("memory testbench starting");

	/**
	 * this simple test bench creates a Memory object and goes
	 * through the collaboration of reserving, allocating, and
	 * releasing memory.
	 */
	uint64_t memSize = 0ll;
	uint64_t baseAddress = 0ll;
	uint64_t endAddress = 0ll;
	if (argc != 2) {
		if (argc == 1) {
			cout << "Setting up a default 16MBytes memory block" << endl;
			memSize = 1024 * 1024 * 16;
		}
		else 
			cout << "Usage: test_bench [memSizeInMBytes]" << endl;
	}
	else {
		memSize = atoi(argv[1]) * 1024 * 1024;
	}

	// use a tiny page size so that page dumps are easier to read
	MobMemory memory(memSize, baseAddress, SIZE_128);

	// reserve a couple 1M blocks
	uint64_t base1 = SIZE_1M;
	if (!memory.reserve(base1, SIZE_1M)) {
		throw "trouble reserving a memory block";
	}
	uint64_t base2 = 5 * SIZE_1M;
	if (!memory.reserve(base2, SIZE_1M)) {
		throw "trouble reserving the second memory block";
	}

	// write a MemoryObject to the first reserved range
	double data[] = { 1.0,2.0,3.0,4.0,5.0,6.0,7.0,8.0,9.0 };
	try {
		MemoryObject mob(sizeof(data) / sizeof(data[0]), MET_REAL64, data);
		memory.write(base1, mob);
		memory.write(base2, mob);
		memory.dumpMemoryContents(cout);
		// inspect the content of the memory
		memory.dumpPages(cout);
		// memory.dumpPageContents(cout, pageNr); 
		// this pageNr is a function of pageSize and the memory write
		// the function dumpPages provides the list of pages that have 
		// data in them. 

		MemoryObject receivingMob(sizeof(data) / sizeof(data[0]), MET_REAL64);
		//		if (memory.read(base1, receivingMob)) {
		//			cout << "Memory Object: " << receivingMob << endl;
		//		}
		memory.read(base1, receivingMob);
		


		// release the blocks
		memory.release(base1);
		memory.release(base2);
	}
	catch (PageException& e) {
		cerr << "Caught PageException: " << e.what() << endl;
	}
	catch (std::runtime_error& e) {
		cerr << e.what() << endl;
	}
	catch (...) {
		cerr << "Caught unexpected error" << endl;
	}
	return 0;
}

