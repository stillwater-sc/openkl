// cpu_blas.cpp: example of BLAS operators using CPU
//
#include <iostream>
#include <openkl/openkl.hpp>

#include <universal/posit/posit>
//#include <universal/posit/posit.hpp>

int main(int argc, char* argv[])
try {
	// first step: enumerate the target devices our program could use
	openkl::klComputeTargets targets;
	openkl::klComputeTargetQuery query = openkl::klComputeTargetQuery{
		openkl::klComputeResource{"",openkl::LOCAL_CPU},
		openkl::klMemoryResource{openkl::MEMORY_NOP,1024,1, 1024}
	};

	if (!openkl::enumerate_targets(targets, query)) {
		std::cerr << "unable to find any OpenKL devices" << std::endl;
		exit(EXIT_FAILURE);
	}

	// second: create an execution context on the device of your choice
	if (!openkl::create_context(targets[0])) {
		std::cerr << "unable to create execution context on device " << targets[0].id << std::endl;
		exit(EXIT_FAILURE);
	}

	for (int i = 0; i < targets.size(); ++i) {
		std::cout << "+-----\n"
			<< " target             : " << targets[i].id << '\n'
			<< " compute class      : " << openkl::klComputeResourceTypeString[targets[i].compute.resourceType] << '\n'
			<< " compute identifier : " << targets[i].compute.id << '\n'
			<< " memory class       : " << openkl::klMemoryResourceTypeString[targets[i].memory.resourceType] << '\n'
			<< " memory size        : " << targets[i].memory.size << " MBytes\n"
			<< " memory channels    : " << targets[i].memory.channels << '\n'
			<< " memory page size   : " << targets[i].memory.pageSize << " kBytes"
			<< std::endl;
	}

	/*
	std::cout << "posit<32,2> epsilon : " << std::numeric_limits< sw::unum::posit<32, 2> >::epsilon() << std::endl;
	std::cout << "posit<32,2> minpos  : " << sw::unum::minpos<32, 2>() << std::endl;
	*/
}
catch(const char* msg) {
	std::cerr << "caught exception: " << msg << std::endl;
}
