// test_bench.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

using namespace std;
using namespace STILLWATER;
using namespace SLM;

int _tmain(int argc, _TCHAR* argv[])
{
	/**
	 * this simple test bench creates a Memory object and goes
	 * through the collaboration of reserving, allocating, and
	 * releasing memory.
	 */
	uint64 memSize = 0ll;
	uint64 baseAddress = 0ll;
	uint64 endAddress = 0ll;
	if (argc != 2) {
		cout << "Usage: test_bench memSizeInMBytes" << endl;
		cout << "Using default 16MBytes" << endl;
		memSize = 1024*1024*16;
	}
	else {
		memSize = atoi(argv[1])*1024*1024;
	}
	endAddress = baseAddress + memSize;
	MobMemory memory(memSize, baseAddress, endAddress, SIZE_4K);

	// reserve a couple 1M blocks
	uint64 base1 = SIZE_1M;
	if (!memory.reserve(SIZE_1M, SIZE_1M)) {
		throw "trouble reserving a memory block";
	}
	uint64 base2 = 5*SIZE_1M;
	if (!memory.reserve(base2, SIZE_1M)) {
		throw "trouble reserving the second memory block";
	}

	// first right a MemoryObject to the first reserved range
	double data[] = { 1.0,2.0,3.0,4.0,5.0,6.0,7.0,8.0,9.0 };
	try {
		MemoryObject mob(sizeof(data)/sizeof(data[0]), MET_REAL64, data);
		memory.write(base1, mob);
		memory.write(base2, mob);
		memory.dumpPages();
		MemoryObject receivingMob(sizeof(data)/sizeof(data[0]), MET_REAL64);
		if (memory.read(base1, receivingMob)) {
			cout << "Memory Object: " << receivingMob << endl;
		}
		// release the blocks
		memory.release(base1);
		memory.release(base2);
	}
	catch (PageException& e) {
		cerr << "Caught PageException: " << e.getMessage() << endl;
	}
	catch (...) {
		cerr << "Caught unexpected error" << endl;
	}
	return 0;
}

